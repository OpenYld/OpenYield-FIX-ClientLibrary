// -------- -------- -------- -------- -------- -------- -------- --------
//
// security_list.cpp
// FixClientLibrary
//
// Copyright © 2024 OpenYield, Inc.
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.
//
// -------- -------- -------- -------- -------- -------- -------- --------

#include "codec/security_list.hpp"

namespace FixClient {

  std::vector<SecurityModel> SecurityCodec::onSecurityList(
    const FIX44::SecurityList& message
  ) const
  {
    std::vector<SecurityModel> data;
    
    FIX::SecurityReqID securityReqID;
    FIX::SecurityResponseID securityResponseID;
    
    message.get(securityReqID);
    message.get(securityResponseID);

    if (message.isSetField(FIX::FIELD::NoRelatedSym)) {
      FIX::NoRelatedSym noRelatedSym;
      message.get(noRelatedSym);
      
      FIX44::SecurityList::NoRelatedSym symGroup;
      FIX::Symbol symbol;
      FIX::SecurityID secID;
      FIX::SecurityIDSource source;
      
      for (int i = 1; i <= noRelatedSym; ++i)
      {
        message.getGroup(i, symGroup);
        symGroup.get(symbol);
        symGroup.get(secID);
        symGroup.get(source);
        
        SecurityCodeKind kind = (
          source == FIX::SecurityIDSource_ISIN_NUMBER
            ? SecurityCodeKind::ISIN
            : SecurityCodeKind::CUSIP
        );
        
        data.push_back(SecurityModel {
          .code = secID,
          .kind = kind
        });
      }
    }
    
    return data;
  }
	

} // Namespace FixClient
