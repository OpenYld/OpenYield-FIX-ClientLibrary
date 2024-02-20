// -------- -------- -------- -------- -------- -------- -------- --------
//
// fix_engine.cpp
// FixClientLibrary
//
// Copyright © 2024 OpenYield, Inc.
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.
//
// -------- -------- -------- -------- -------- -------- -------- --------

#include <regex>

#include <fmt/core.h>

#include "fix_engine.hpp"

namespace FixClient {

  FixEngine::FixEngine(
    std::shared_ptr<WorkflowInterface> workflow
  ) :
    workflow_(workflow)
  {
    // Nada
  }

// -------- -------- -------- -------- -------- -------- -------- --------
// MARK: FIX Boilerplate

  void FixEngine::onCreate(const FIX::SessionID& sessionID)
  {
    log_.logDebug(fmt::format("[{}]/onCreate", sessionID.toStringFrozen()));
  }

  void FixEngine::onLogon(const FIX::SessionID& sessionID)
  {
    log_.logDebug(fmt::format("[{}]/onLogon", sessionID.toStringFrozen()));
    workflow_->onLogon(sessionID.getSenderCompID());
  }

  void FixEngine::onLogout(const FIX::SessionID& sessionID)
  {
    log_.logDebug(fmt::format("[{}]/onLogout", sessionID.toStringFrozen()));
    workflow_->onLogout(sessionID.getSenderCompID());
  }

  void FixEngine::toAdmin(FIX::Message& message,
    const FIX::SessionID& sessionID)
  {
    std::string msgType = message.getHeader().getField(FIX::FIELD::MsgType);

    // No need to log these
    if ( msgType == FIX::MsgType_Heartbeat
      || msgType == FIX::MsgType_Logon
      || msgType == FIX::MsgType_Logout
    ) {
      return;
    }

    // We want to log these
    // 1 Test Message
    // 2 Resend Request
    // 3 Reject
    // 4 Sequence Reset

    log_.logDebug(
      fmt::format(
        "[{}]/toAdmin: {}",
        sessionID.toStringFrozen(),
        std::regex_replace(message.toString(), std::regex("\1"), " ")
      )
    );
  }

  void FixEngine::fromAdmin(const FIX::Message& message,
    const FIX::SessionID& sessionID)
  {
    std::string msgType = message.getHeader().getField(FIX::FIELD::MsgType);

    // No need to log these
    if ( msgType == FIX::MsgType_Heartbeat
      || msgType == FIX::MsgType_Logon
      || msgType == FIX::MsgType_Logout
    ) {
      return;
    }

    // We want to log these
    // 1 Test Message
    // 2 Resend Request
    // 3 Reject
    // 4 Sequence Reset

    log_.logDebug(
      fmt::format(
        "[{}]/fromAdmin: {}",
        sessionID.toStringFrozen(),
        std::regex_replace(message.toString(), std::regex("\1"), " ")
      )
    );
  }

  void FixEngine::toApp([[maybe_unused]] FIX::Message& message,
    [[maybe_unused]] const FIX::SessionID& sessionID)
  {
    // Nothing here
  }

  // Crack messages and pass them on to the virtual handlers below. Rejects
  // anything else!
  void FixEngine::fromApp(const FIX::Message& message,
    const FIX::SessionID& sessionID)
  {
    try {
      crack(message, sessionID);
    } catch (FIX::UnsupportedMessageType& e) {
      log_.logWarning(
        fmt::format(
          "[{}]/fromApp: Unsupported Message: {}",
          sessionID.toStringFrozen(),
          std::regex_replace(message.toString(), std::regex("\1"), " ")
        )
      );
    }
  }
  
  void FixEngine::onMessage(
    const FIX44::ExecutionReport& message,
    [[ maybe_unused ]] const FIX::SessionID& session
  )
  {
    std::optional<ExecutionEventModel> optionalData =
      executionEventCodec_.onExecutionReport(message);
      
    if (!optionalData.has_value()) {
      return;
    }
    
    ExecutionEventModel data = optionalData.value();
      
    if (std::holds_alternative<AcknowledgeEventModel>(data.value)) {
      workflow_->onAcknowledgeEvent(
        data.orderCode,
        std::get<AcknowledgeEventModel>(data.value)
      );
      return;
    }

    if (std::holds_alternative<RejectEventModel>(data.value)) {
      workflow_->onRejectEvent(
        data.orderCode,
        std::get<RejectEventModel>(data.value)
      );
      return;
    }

    if (std::holds_alternative<FillEventModel>(data.value)) {
      workflow_->onFillEvent(
        data.orderCode,
        std::get<FillEventModel>(data.value)
      );
      return;
    }

    if (std::holds_alternative<PostTradeEventModel>(data.value)) {
      workflow_->onPostTradeEvent(
        data.orderCode,
        std::get<PostTradeEventModel>(data.value)
      );
      return;
    }
    
    log_.logCritic("Unhandled Execution Event!");
  }

} // Namespace FixClient
