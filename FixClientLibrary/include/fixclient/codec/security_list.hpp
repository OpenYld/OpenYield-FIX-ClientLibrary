// -------- -------- -------- -------- -------- -------- -------- --------
//
// security_list.hpp
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
//    │  FIX Security List                                            │░░
//    │                                                               │░░
//    │  - List of supported security identifiers                     │░░
//    │                                                               │░░
//    └───────────────────────────────────────────────────────────────┘░░
//      ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
//      ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
//
// -------- -------- -------- -------- -------- -------- -------- --------

#pragma once

#include <string>

#include "quickfix.hpp"
#include "../model/security_model.hpp"

namespace FixClient {

  // -------- -------- -------- -------- -------- -------- -------- --------
  // MARK: Security Codec

  class SecurityCodec
  {
  
    public:
    
      std::vector<SecurityModel> onSecurityList(
        const FIX44::SecurityList& message
      ) const;

    private:
  
  };

} // Namespace FixClient
