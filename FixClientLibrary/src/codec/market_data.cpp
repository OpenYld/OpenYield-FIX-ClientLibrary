// -------- -------- -------- -------- -------- -------- -------- --------
//
// market_data.cpp
// FixClientLibrary
//
// Copyright © 2024 OpenYield, Inc.
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.
//
// -------- -------- -------- -------- -------- -------- -------- --------

#include "codec/market_data.hpp"

namespace FixClient {

// -------- -------- -------- -------- -------- -------- -------- --------
// MARK: Market Data Codec

  std::vector<MarketDataModel>
  MarketDataCodec::onMarketDataSnapshotFullRefresh(
    const FIX44::MarketDataSnapshotFullRefresh& message) const
  {
    std::vector<MarketDataModel> data;
    
    FIX::SecurityID securityId;
    message.get(securityId);

    FIX::NoMDEntries noMDEntries;
    message.get(noMDEntries);

    FIX44::MarketDataSnapshotFullRefresh::NoMDEntries group;
    FIX::MDEntryType mdEntryType;
    FIX::MDEntryPx mdEntryPx;
    FIX::MDEntrySize mdEntrySize;
    FIX::PriceDelta priceDelta;

    for (auto i = 1; i <= noMDEntries; ++i) {
      message.getGroup(i, group);

      group.get(mdEntryType);
      group.get(mdEntryPx);
      group.get(mdEntrySize);
      group.get(priceDelta);

      data.push_back( MarketDataModel {
        .action = FIX::MDUpdateAction_NEW,
        .entryType = mdEntryType,
        .securityCode = securityId,
        .quantity = mdEntrySize,
        .price = mdEntryPx,
        .yield = priceDelta
      });
      
    }
    
    return data;
  }

  std::vector<MarketDataModel>
  MarketDataCodec::onMarketDataIncrementalRefresh(
    const FIX44::MarketDataIncrementalRefresh& message) const
  {
    std::vector<MarketDataModel> data;
    
    FIX::NoMDEntries noMDEntries;
    message.get(noMDEntries);

    FIX44::MarketDataIncrementalRefresh::NoMDEntries group;
    FIX::MDUpdateAction mdUpdateAction;
    FIX::SecurityID securityId;
    FIX::MDEntryType mdEntryType;
    FIX::MDEntryPx mdEntryPx;
    FIX::MDEntrySize mdEntrySize;
    FIX::PriceDelta priceDelta;

    for (auto i = 1; i <= noMDEntries; ++i) {
      message.getGroup(i, group);

      group.get(mdUpdateAction);
      group.get(securityId);
      group.get(mdEntryType);
      group.get(mdEntryPx);
      group.get(mdEntrySize);
      group.get(priceDelta);

      data.push_back( MarketDataModel {
        .action = mdUpdateAction,
        .entryType = mdEntryType,
        .securityCode = securityId,
        .quantity = mdEntrySize,
        .price = mdEntryPx,
        .yield = priceDelta
      });
      
    }
    
    return data;
  }


} // Namespace FixClient
