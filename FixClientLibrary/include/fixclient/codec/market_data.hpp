// -------- -------- -------- -------- -------- -------- -------- --------
//
// market_data.hpp
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
//    │  FIX Market Data                                              │░░
//    │                                                               │░░
//    │  - Snapshot on Connect                                        │░░
//    │  - Incremental Update After                                   │░░
//    │                                                               │░░
//    │  Content                                                      │░░
//    │  - Best Bid and Best Offer                                    │░░
//    │  - Open Price (Yesterday's Close Price)                       │░░
//    │  - Daily High and Low Price                                   │░░
//    │  - Index (Mid delta to Open Price)                            │░░
//    │  - Trade (OpenYield Prints)                                   │░░
//    │                                                               │░░
//    └───────────────────────────────────────────────────────────────┘░░
//      ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
//      ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
//
// The Market Data feed sends Open, Bid, Offer, High, Low and Index (if
// available) on connection. After that, it sends updates. The key is
// the security code.
//
// Special cases:
// - The TRADE message indicates an actual pringt on the OpenYield
//   Marketplace
// - The INDEX message is an indicative value to show if the market is
//   up or down on the day
//
// -------- -------- -------- -------- -------- -------- -------- --------

#pragma once

#include <string>
#include <vector>

#include "quickfix.hpp"

namespace FixClient {

  // -------- -------- -------- -------- -------- -------- -------- --------
  // MARK: Market Data Model

  struct MarketDataModel
  {
    // FIX::MDUpdateAction
    // Supported values are
    //   const char MDUpdateAction_NEW = '0';
    //   const char MDUpdateAction_CHANGE = '1';
    //   const char MDUpdateAction_DELETE = '2';
    char action;
    
    // FIX::MDEntryType
    // Supported values are
    //   const char MDEntryType_BID = '0';
    //   const char MDEntryType_OFFER = '1';
    //   const char MDEntryType_TRADE = '2';
    //   const char MDEntryType_INDEX_VALUE = '3';
    //   const char MDEntryType_OPENING_PRICE = '4';
    //   const char MDEntryType_TRADING_SESSION_HIGH_PRICE = '7';
    //   const char MDEntryType_TRADING_SESSION_LOW_PRICE = '8';
    char entryType;
    
    // FIX::SecurityID (ISIN or CUSIP as configured)
    std::string securityCode;
    
    // FIX::MDEntrySize
    double quantity;
    
    // FIX::MDEntryPx
    double price;
    
    // FIX::PriceDelta
    // NOTE: Standard FIX does not offer a Yield field in Market
    // data messages, so we chose the PriceDelta field.
    double yield;
  
  };

  // -------- -------- -------- -------- -------- -------- -------- --------
  // MARK: Market Data Codec

  class MarketDataCodec
  {
  
    public:
    
      std::vector<MarketDataModel> onMarketDataSnapshotFullRefresh(
        const FIX44::MarketDataSnapshotFullRefresh& message
      ) const;

      std::vector<MarketDataModel> onMarketDataIncrementalRefresh(
        const FIX44::MarketDataIncrementalRefresh& message
      ) const;

    private:
  
  };

} // Namespace FixClient
