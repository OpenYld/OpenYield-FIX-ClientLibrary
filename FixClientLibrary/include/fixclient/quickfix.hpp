// -------- -------- -------- -------- -------- -------- -------- --------
//
// quickfix.hpp
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

// SPECIAL: Pulled this out so compiler warnings go away!

#pragma GCC diagnostic push
// #pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma GCC diagnostic ignored "-Wunused-parameter"

#if defined(__clang__)
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wmissing-field-initializers"
  #pragma clang diagnostic ignored "-Wignored-qualifiers"
  #pragma clang diagnostic ignored "-Wdeprecated-copy-with-user-provided-copy"
#endif

// Fix
#include <quickfix/config.h>
#include <quickfix/Application.h>
#include <quickfix/Group.h>
#include <quickfix/FileLog.h>
#include <quickfix/FileStore.h>
#include <quickfix/SocketInitiator.h>
#include <quickfix/fix44/MessageCracker.h>

// Messages
#include <quickfix/fix44/ExecutionReport.h>
#include <quickfix/fix44/MarketDataIncrementalRefresh.h>
#include <quickfix/fix44/MarketDataSnapshotFullRefresh.h>
#include <quickfix/fix44/NewOrderSingle.h>
#include <quickfix/fix44/OrderCancelReplaceRequest.h>
#include <quickfix/fix44/OrderCancelRequest.h>
#include <quickfix/fix44/TradingSessionStatus.h>
#include <quickfix/fix44/IOI.h>
#include <quickfix/fix44/SecurityListRequest.h>
#include <quickfix/fix44/SecurityList.h>
#include <quickfix/fix44/QuoteCancel.h>

#if defined(__clang__)
  #pragma clang diagnostic pop
#endif

#pragma GCC diagnostic pop
