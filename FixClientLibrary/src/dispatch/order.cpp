// -------- -------- -------- -------- -------- -------- -------- --------
//
// order.cpp
// FixClientLibrary
//
// Copyright © 2024 OpenYield, Inc.
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.
//
// -------- -------- -------- -------- -------- -------- -------- --------

#include <fmt/core.h>

#include "dispatch/order.hpp"

namespace FixClient {

	OrderDispatch::OrderDispatch(
    const std::string& senderCompId
  ) :
    senderCompId_(senderCompId + "-TR")
  {}
  
  void OrderDispatch::sendOrder(const OrderModel& model)
  {
    switch (model.action) {
      case OrderAction::New:
        sendNewOrder(model);
        break;

      case OrderAction::Replace:
        sendReplaceOrder(model);
        break;

      case OrderAction::Cancel:
        sendCancelOrder(model);
        break;
    }
  }
  
  void OrderDispatch::sendNewOrder(const OrderModel& model)
  {
    FIX::Side side = (
      model.side == OrderSide::Sell ? FIX::Side_SELL : FIX::Side_BUY
    );

    FIX::OrdType ordType = (
      model.kind ==
        OrderKind::Market ? FIX::OrdType_MARKET : FIX::OrdType_LIMIT
    );
    
    auto securityIdSource = (
      model.security.kind == SecurityCodeKind::ISIN
        ? FIX::SecurityIDSource_ISIN_NUMBER
        : FIX::SecurityIDSource_CUSIP
    );

    FIX44::NewOrderSingle message(
      FIX::ClOrdID(model.orderCode),
      side,
      FIX::TransactTime(),
      ordType
    );

    FIX44::NewOrderSingle::NoPartyIDs partyGroup;
    partyGroup.set(FIX::PartyID(model.counterpartyCode));
    partyGroup.set(FIX::PartyRole(FIX::PartyRole_CLIENT_ID));
    message.set(FIX::NoPartyIDs(1));
    message.addGroup(partyGroup);
    
    message.set(FIX::Symbol(model.security.code));
    message.set(FIX::SecurityID(model.security.code));
    message.set(FIX::SecurityIDSource(securityIdSource));
    
    message.set(FIX::OrderQty(model.quantity));

    message.set(FIX::PriceType(FIX::PriceType_PERCENTAGE));
    message.set(FIX::Price(model.price));

    FIX::Session::sendToTarget(message,
      FIX::SenderCompID(senderCompId_),
      FIX::TargetCompID("OPENYIELD-TR")
    );
    
    log_.logDebug(
      fmt::format("NEW Order to {}: {}", senderCompId_, message.toString())
    );
  }

  void OrderDispatch::sendReplaceOrder(const OrderModel& model)
  {
    FIX::Side side = (
      model.side == OrderSide::Sell ? FIX::Side_SELL : FIX::Side_BUY
    );

    FIX::OrdType ordType = (
      model.kind ==
        OrderKind::Market ? FIX::OrdType_MARKET : FIX::OrdType_LIMIT
    );
    
    auto securityIdSource = (
      model.security.kind == SecurityCodeKind::ISIN
        ? FIX::SecurityIDSource_ISIN_NUMBER
        : FIX::SecurityIDSource_CUSIP
    );
    
    FIX44::OrderCancelReplaceRequest message(
      FIX::OrigClOrdID(model.originalOrderCode),
      FIX::ClOrdID(model.orderCode),
      side,
      FIX::TransactTime(),
      ordType
    );

    FIX44::OrderCancelReplaceRequest::NoPartyIDs partyGroup;
    partyGroup.set(FIX::PartyID(model.counterpartyCode));
    partyGroup.set(FIX::PartyRole(FIX::PartyRole_CLIENT_ID));
    message.set(FIX::NoPartyIDs(1));
    message.addGroup(partyGroup);
    
    message.set(FIX::Symbol(model.security.code));
    message.set(FIX::SecurityID(model.security.code));
    message.set(FIX::SecurityIDSource(securityIdSource));
    
    message.set(FIX::OrderQty(model.quantity));

    message.set(FIX::PriceType(FIX::PriceType_PERCENTAGE));
    message.set(FIX::Price(model.price));

    FIX::Session::sendToTarget(message,
      FIX::SenderCompID(senderCompId_),
      FIX::TargetCompID("OPENYIELD-TR")
    );
    
    log_.logDebug(
      fmt::format("REPLACE Order to {}: {}", senderCompId_, message.toString())
    );
  }
  
  void OrderDispatch::sendCancelOrder(const OrderModel &model)
  {
    FIX::Side side = (
      model.side == OrderSide::Sell ? FIX::Side_SELL : FIX::Side_BUY
    );

    FIX::OrdType ordType = (
      model.kind ==
        OrderKind::Market ? FIX::OrdType_MARKET : FIX::OrdType_LIMIT
    );
    
    auto securityIdSource = (
      model.security.kind == SecurityCodeKind::ISIN
        ? FIX::SecurityIDSource_ISIN_NUMBER
        : FIX::SecurityIDSource_CUSIP
    );
    
    FIX44::OrderCancelReplaceRequest message(
      FIX::OrigClOrdID(model.originalOrderCode),
      FIX::ClOrdID(model.orderCode),
      side,
      FIX::TransactTime(),
      ordType
    );
    
    FIX44::OrderCancelRequest::NoPartyIDs partyGroup;
    partyGroup.set(FIX::PartyID(model.counterpartyCode));
    partyGroup.set(FIX::PartyRole(FIX::PartyRole_CLIENT_ID));
    message.set(FIX::NoPartyIDs(1));
    message.addGroup(partyGroup);
    
    message.set(FIX::Symbol(model.security.code));
    message.set(FIX::SecurityID(model.security.code));
    message.set(FIX::SecurityIDSource(securityIdSource));
    
    message.set(FIX::OrderQty(0));

    FIX::Session::sendToTarget(message,
      FIX::SenderCompID(senderCompId_),
      FIX::TargetCompID("OPENYIELD-TR")
    );
    
    log_.logDebug(
      fmt::format("CANCEL Order to {}: {}", senderCompId_, message.toString())
    );

  }

} // Namespace FixClient
