// -------- -------- -------- -------- -------- -------- -------- --------
//
// session_state.cpp
// FixClientLibrary
//
// Copyright © 2024 OpenYield, Inc.
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.
//
// -------- -------- -------- -------- -------- -------- -------- --------

#include "codec/session_state.hpp"

namespace FixClient {

	SessionStateModel SessionStateCodec::onTradingSessionStatus(
    const FIX44::TradingSessionStatus& message) const
  {
    FIX::TradSesStatus tradSesStatus;
    message.get(tradSesStatus);
  
    return SessionStateModel {
      .sessionState = tradSesStatus
    };
  }

} // Namespace FixClient
