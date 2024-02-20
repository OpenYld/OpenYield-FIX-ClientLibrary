// -------- -------- -------- -------- -------- -------- -------- --------
//
// security_model.hpp
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

#include <string>

namespace FixClient {

  // -------- -------- -------- -------- -------- -------- -------- --------
  // MARK: Security Code Kind

	enum class SecurityCodeKind {

    ISIN,
  
    CUSIP
  
  };
  
  // -------- -------- -------- -------- -------- -------- -------- --------
  // MARK: Security Model

  struct SecurityModel
  {
    
    std::string code;
    
    SecurityCodeKind kind;
  
  };

} // Namespace FixClient
