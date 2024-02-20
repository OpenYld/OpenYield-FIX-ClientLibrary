// -------- -------- -------- -------- -------- -------- -------- --------
//
// workflow.hpp
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

#include <string>

#include "codec/market_data.hpp"
#include "codec/session_state.hpp"
#include "codec/execution_event.hpp"
#include "codec/order_book.hpp"

#include "dispatch/order.hpp"

namespace FixClient {

  class WorkflowInterface
  {
    
    public:
    
      // Construct the interface using the provided
      // FIX Comp ID. Do not append the "-MD", "-TR", as the library knows!
      WorkflowInterface(const std::string& compId);
    
      // -------- -------- -------- --------
      // MARK: Incoming Overrides
    
      // Override this function to handle login events
      void onLogon(const std::string& senderId) const;

      // Override this function to handle logout events
      void onLogout(const std::string& senderId) const;
      
      // Override this to consume market data messages
      void onMarketData(const std::vector<MarketDataModel>& model) const;

      // Override this to consume order book depth messages
      void onOIOOrderBook(const IOIOrderModel& model) const;

      // Override this to capture marketplace session state
      void onSessionState(const SessionStateModel& model) const;
      
      // Override the next four to handle the different
      // workflows provided by execution reports
      void onAcknowledgeEvent(const std::string& orderCode,
        const AcknowledgeEventModel& model) const;

      void onRejectEvent(const std::string& orderCode,
        const RejectEventModel& model) const;

      void onFillEvent(const std::string& orderCode,
        const FillEventModel& model) const;

      void onPostTradeEvent(const std::string& orderCode,
        const PostTradeEventModel& model) const;
        
      // -------- -------- -------- --------
      // MARK: Outgoing Functions
      
      // Place a new order, replace it or cancel it
      void sendOrder(const OrderModel& model);
      
      // Request a list of supported securities
      void requestSecurityList();

      // Send Cancel All
      void sendCancelAll();

    private:
    
      OrderDispatch orderDispatch_;
  
  };

} // Namespace FixClient
