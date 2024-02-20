// -------- -------- -------- -------- -------- -------- -------- --------
//
// log.cpp
// FixClientLibrary
//
// Copyright © 2024 OpenYield, Inc.
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.
//
// -------- -------- -------- -------- -------- -------- -------- --------

#include "log.hpp"

namespace FixClient {

void Log::log(const std::string logLevel,
  const std::string_view& logMessage) const
{
#ifdef SCAFFOLD
    if (logLevel == "DEBUG") {
      LOGDEBUG(logMessage);
    }
    if (logLevel == "INFO") {
      LOGINFO(logMessage);
    }
    if (logLevel == "WARNING") {
      LOGWARNING(logMessage);
    }
    if (logLevel == "ERROR") {
      LOGERROR(logMessage);
    }
    if (logLevel == "CRITIC") {
      LOGCRITIC(logMessage);
    }
#else
    std::cout << logLevel << ": " << logMessage << std::endl;
#endif
  }

} // Namespace FixClient
