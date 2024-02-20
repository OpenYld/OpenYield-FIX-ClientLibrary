// -------- -------- -------- -------- -------- -------- -------- --------
//
// workflow.cpp
// FixClientLibrary
//
// Copyright © 2024 OpenYield, Inc.
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.
//
// -------- -------- -------- -------- -------- -------- -------- --------

#include "workflow.hpp"

namespace FixClient {

  WorkflowInterface::WorkflowInterface(
    const std::string& compId
  ) :
    orderDispatch_(compId)
  {}

  void WorkflowInterface::onLogon(
    [[ maybe_unused ]] const std::string& senderId) const
  {
    // Do nothing by default
  }

  void WorkflowInterface::onLogout(
    [[ maybe_unused ]] const std::string& senderId) const
  {
    // Do nothing by default
  }
  
  void WorkflowInterface::onMarketData(
    [[ maybe_unused ]] const std::vector<MarketDataModel>& model) const
  {
    // Do nothing by default
  }

  void WorkflowInterface::onOIOOrderBook(
    [[ maybe_unused ]] const IOIOrderModel& model) const
  {
    // Do nothing by default
  }
  
  void WorkflowInterface::onSessionState(
    [[ maybe_unused ]] const SessionStateModel& model) const
  {
    // Do nothing by default
  }
  
  void WorkflowInterface::onAcknowledgeEvent(
    [[ maybe_unused ]] const std::string& orderCode,
    [[ maybe_unused ]] const AcknowledgeEventModel& model) const
  {
    // Do nothing by default
  }

  void WorkflowInterface::onRejectEvent(
    [[ maybe_unused ]] const std::string& orderCode,
    [[ maybe_unused ]] const RejectEventModel& model) const
  {
    // Do nothing by default
  }

  void WorkflowInterface::onFillEvent(
    [[ maybe_unused ]] const std::string& orderCode,
    [[ maybe_unused ]]   const FillEventModel& model) const
  {
    // Do nothing by default
  }
  
  void WorkflowInterface::onPostTradeEvent(
    [[ maybe_unused ]] const std::string& orderCode,
    [[ maybe_unused ]] const PostTradeEventModel& model) const
  {
    // Do nothing by default
  }
  
  void WorkflowInterface::sendOrder(const OrderModel& model)
  {
    orderDispatch_.sendOrder(model);
  }
  
  void WorkflowInterface::requestSecurityList()
  {
    FIX44::SecurityListRequest message;
    message.set(FIX::SecurityReqID("1"));
    message.set(FIX::SecurityListRequestType(
      FIX::SecurityListRequestType_ALL_SECURITIES)
    );
    
    FIX::Session::sendToTarget(message,
      FIX::SenderCompID(orderDispatch_.senderCompId()),
      FIX::TargetCompID("OPENYIELD-TR")
    );

  }
  
  void WorkflowInterface::sendCancelAll()
  {
    FIX44::QuoteCancel message(
      FIX::QuoteID("YourQuoteId"),
      FIX::QuoteCancelType(FIX::QuoteCancelType_CANCEL_ALL_QUOTES)
    );
    
    // For shared connections, set the PartyRole_CLIENT_ID in a
    // party group to cancel orders for that party only

    FIX::Session::sendToTarget(message,
      FIX::SenderCompID(orderDispatch_.senderCompId()),
      FIX::TargetCompID("OPENYIELD-TR")
    );
    
  }

} // Namespace FixClient
