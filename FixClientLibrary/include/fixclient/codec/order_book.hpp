// -------- -------- -------- -------- -------- -------- -------- --------
//
// order_book.hpp
// FixClientLibrary
//
// Copyright © 2024 OpenYield, Inc.
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.
//
// -------- -------- -------- -------- -------- -------- -------- --------
//
//    ┌───────────────────────────────────────────────────────────────┐  
//    │                                                               │  
//    │  FIX Order Book                                               │░░
//    │                                                               │░░
//    │  - Builds depth of book as orders are created and updated     │░░
//    │                                                               │░░
//    └───────────────────────────────────────────────────────────────┘░░
//      ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
//      ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
//
// This feed provides the Order Book in the form of a FIX IOI message. Each
// order has a unique ID so you can map messages to your order book or
// aggregation handler. Each order price is what you can execute at. Your
// own orders as set as "isMine".
//
// -------- -------- -------- -------- -------- -------- -------- --------

#pragma once

#include <string>

#include "quickfix.hpp"

namespace FixClient {

	struct IOIOrderModel
  {
    // The IOIOrderCode being created, updated or canceled
    std::string ioiCode;
    
    // Values are
    //   Create
    //   Update
    //   Delete
    std::string action;
    
    // FIX::SecurityID (ISIN or CUSIP as configured)
    std::string securityCode;
    
    // Values are
    //   Bid
    //   Offer
    std::string bidOrOffer;
    
    // Quantity (zero for cancels)
    double quantity;
    
    // Order Price (zero for cancels)
    double price;
    
    // Order Yield
    double yield;
    
    // True if the order is one of mine
    // Values are
    //   NotMine
    //   IsMine
    //   MaybeMine (on shared FIX connections only)
    std::string isMine;
    
  };
  
  // -------- -------- -------- -------- -------- -------- -------- --------
  // MARK: Order Book Codec

  class OrderBookCodec
  {
  
    public:
    
      IOIOrderModel onIOI(
        const FIX44::IOI& message
      ) const;

    private:
  
  };

} // Namespace FixClient
