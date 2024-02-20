// -------- -------- -------- -------- -------- -------- -------- --------
//
// order_book.cpp
// FixClientLibrary
//
// Copyright © 2024 OpenYield, Inc.
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.
//
// -------- -------- -------- -------- -------- -------- -------- --------

#include "codec/order_book.hpp"

namespace FixClient {

  IOIOrderModel OrderBookCodec::onIOI(const FIX44::IOI& message) const
  {
    FIX::IOIID ioiId;
    FIX::IOITransType ioiTransType;
    FIX::SecurityID securityId;
    FIX::Side side;
    FIX::IOIQty ioiQuantity;
    FIX::Price price;
    FIX::Yield yield;
    FIX::IOIQltyInd ioiQltyInd;

    message.get(ioiId);
    message.get(ioiTransType);
    message.get(securityId);
    message.get(side);
    message.get(ioiQuantity);
    message.get(price);
    message.get(yield);
    message.get(ioiQltyInd);
    
    IOIOrderModel model;
    
    model.ioiCode = ioiId;
    
    model.action = "Update";
    if (ioiTransType == FIX::IOITransType_CANCEL) {
      model.action = "Delete";
    }
    if (ioiTransType == FIX::IOITransType_NEW) {
      model.action = "Create";
    }

    model.securityCode = securityId;
    
    model.bidOrOffer = "Offer";
    if (side == FIX::Side_BUY) {
      model.bidOrOffer = "Bid";
    }
    
    model.quantity = 0.0;
    try {
      model.quantity = std::stod(ioiQuantity);
    } catch (...) {
      // DO NOTHING
    }

    model.price = price;
    model.yield = yield;

    model.isMine = "NotMine";
    if (ioiQltyInd == FIX::IOIQltyInd_LOW) {
      model.isMine = "IsMine";
    }
    if (ioiQltyInd == FIX::IOIQltyInd_MEDIUM) {
      model.isMine = "MaybeMine";
    }
    
    return model;
  }

} // Namespace FixClient
