// -------- -------- -------- -------- -------- -------- -------- --------
//
// log.hpp
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

#ifdef SCAFFOLD
  #include <core/log/log.hpp>
#else
  #include <iostream>
#endif

namespace FixClient {

  class Log {

  public:

    inline void logDebug(const std::string_view& logMessage) const
    {
      log("DEBUG", logMessage);
    }

    inline void logInfo(const std::string_view& logMessage) const
    {
      log("INFO", logMessage);
    }

    inline void logWarning(const std::string_view& logMessage) const
    {
      log("WARNING", logMessage);
    }

    inline void logError(const std::string_view& logMessage) const
    {
      log("ERROR", logMessage);
    }

    inline void logCritic(const std::string_view& logMessage) const
    {
      log("CRITIC", logMessage);
    }

  private:

    void log(const std::string logLevel,
      const std::string_view& logMessage) const;

  };

} // Namespace FixClient
