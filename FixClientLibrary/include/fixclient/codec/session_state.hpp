// -------- -------- -------- -------- -------- -------- -------- --------
//
// session_state.hpp
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
//    │  FIX Session State                                            │░░
//    │                                                               │░░
//    │  - Sent on connection                                         │░░
//    │  - Updates on state change                                    │░░
//    │                                                               │░░
//    │  States are                                                   │░░
//    │  - Closed                                                     │░░
//    │  - Pre-Open                                                   │░░
//    │  - Open                                                       │░░
//    │  - Halted                                                     │░░
//    │                                                               │░░
//    └───────────────────────────────────────────────────────────────┘░░
//      ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
//      ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
//
// -------- -------- -------- -------- -------- -------- -------- --------

#pragma once

#include "quickfix.hpp"

namespace FixClient {

  // -------- -------- -------- -------- -------- -------- -------- --------
  // MARK: Session State Model
  
  struct SessionStateModel
  {
    // FIX::TradSesStatus
    // Supported Values are
    //   const int TradSesStatus_HALTED = 1;
    //   const int TradSesStatus_OPEN = 2;
    //   const int TradSesStatus_CLOSED = 3;
    //   const int TradSesStatus_PRE_OPEN = 4;
    int sessionState;

  };
  
  // -------- -------- -------- -------- -------- -------- -------- --------
  // MARK: Session State Codec

  class SessionStateCodec
  {
  
    public:
    
      SessionStateModel onTradingSessionStatus(
        const FIX44::TradingSessionStatus& message
      ) const;

    private:
  
  };

} // Namespace FixClient
