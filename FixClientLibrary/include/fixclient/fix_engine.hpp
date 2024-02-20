// -------- -------- -------- -------- -------- -------- -------- --------
//
// fix_engine.hpp
// FixClientLibrary
//
// Copyright © 2024 OpenYield, Inc.
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.
//
// -------- -------- -------- -------- -------- -------- -------- --------

#pragma once

#include <variant>

#include "log.hpp"
#include "quickfix.hpp"
#include "workflow.hpp"
#include "codec/market_data.hpp"
#include "codec/session_state.hpp"
#include "codec/execution_event.hpp"
#include "codec/order_book.hpp"

namespace FixClient {

  class FixEngine : public FIX::Application, public FIX44::MessageCracker
  {

  public:
  
    FixEngine(std::shared_ptr<WorkflowInterface> workflow);

  // -------- -------- -------- -------- -------- -------- -------- --------
  // MARK: QuickFIX Boilerplate

    void onCreate(const FIX::SessionID& sessionID) override;

    void onLogon(const FIX::SessionID& sessionID) override;

    void onLogout(const FIX::SessionID& sessionID) override;

    void toAdmin(FIX::Message& message,
      const FIX::SessionID& sessionID) override;

    void toApp(FIX::Message& message,
      const FIX::SessionID& sessionID) override;

    void fromAdmin(
      const FIX::Message& message,
      const FIX::SessionID& sessionID) override;

    void fromApp(const FIX::Message& message,
      const FIX::SessionID& sessionID) override;

  private:
  
  // -------- -------- -------- -------- -------- -------- -------- --------
  // MARK: OPENYIELD-MD
  
  
    // -------- -------- -------- --------
    // MARK: Market Data Messages

    // After successful connection to the MD feed, will
    // receive a full top of market snapshot here
    void onMessage(
      const FIX44::MarketDataSnapshotFullRefresh& message,
      [[ maybe_unused ]] const FIX::SessionID& session
    ) override
    {
      workflow_->onMarketData(
        marketDataCodec_.onMarketDataSnapshotFullRefresh(message)
      );
    }

    // After the snapshot is done, any changes come as incremental
    // refreshes
    void onMessage(
      const FIX44::MarketDataIncrementalRefresh& message,
      [[ maybe_unused ]] const FIX::SessionID& session
    ) override
    {
      workflow_->onMarketData(
        marketDataCodec_.onMarketDataIncrementalRefresh(message)
      );
    }

  // -------- -------- -------- -------- -------- -------- -------- --------
  // MARK: OPENYIELD-OB
  
  
    // -------- -------- -------- --------
    // MARK: IOI Messages
    
    void onMessage(
      const FIX44::IOI& message,
      [[ maybe_unused ]] const FIX::SessionID& session
    ) override
    {
      workflow_->onOIOOrderBook(
        orderBookCodec_.onIOI(message)
      );
    }

  // -------- -------- -------- -------- -------- -------- -------- --------
  // MARK: OPENYIELD-TR

    // -------- -------- -------- --------
    // MARK: Execution Report Messages

    void onMessage(
      const FIX44::ExecutionReport& message,
      [[ maybe_unused ]] const FIX::SessionID& session
    ) override;
  
    // -------- -------- -------- --------
    // MARK: Session State Messages

    void onMessage(
      const FIX44::TradingSessionStatus& message,
      [[ maybe_unused ]] const FIX::SessionID& session
    ) override
    {
      workflow_->onSessionState(
        sessionStateCodec_.onTradingSessionStatus(message)
      );
    }

  // -------- -------- -------- -------- -------- -------- -------- --------
  // MARK: Private Properties

    // A logger to print out what happened
    Log log_;
    
    // Override this to consume FIX data
    std::shared_ptr<WorkflowInterface> workflow_;
    
    // Codecs
    MarketDataCodec marketDataCodec_;
    SessionStateCodec sessionStateCodec_;
    ExecutionEventCodec executionEventCodec_;
    OrderBookCodec orderBookCodec_;

  };

} // Namespace FixClient
