// -------- -------- -------- -------- -------- -------- -------- --------
//
// execution_event.hpp
// FixClientLibrary
//
// Copyright © 2024 OpenYield, Inc.
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.
//
// -------- -------- -------- -------- -------- -------- -------- --------
// ┌───────────────────────────────────────────────────────────────┐
// │                                                               │  
// │  FIX Execution Report                                         │░░
// │                                                               │░░
// │  - Order Acknowledgement                                      │░░
// │  - Order Rejection                                            │░░
// │  - Order Fill                                                 │░░
// │  - Post Trade Cancel or Correct                               │░░
// │                                                               │░░
// └───────────────────────────────────────────────────────────────┘░░
//   ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
//   ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
//
// FIX Execution Reports are used for four different kinds of messaging
// from the Marketplace. This file parses an Execution Report and generates
// one of the four responses based on the content.
//
// -------- -------- -------- -------- -------- -------- -------- --------

#pragma once

#include <variant>
#include <optional>

#include "log.hpp"
#include "quickfix.hpp"

namespace FixClient {

  // -------- -------- -------- -------- -------- -------- -------- --------
  // MARK: Acknowledge Event Model
  //
  // Acknowledgements are messages that acknowledge an order create,
  // cancel or replacement on the marketplace

  struct AcknowledgeEventModel {
    
    // Values are
    //   NewOrderAccepted
    //   OrderCanceled
    //   OrderReplaced
    std::string status;
    
    // Why it happened
    std::string reason { "" };

  };
  
  // -------- -------- -------- -------- -------- -------- -------- --------
  // MARK: Reject Event Model
  //
  // Rejections are messages that explain why an order create,
  // cancel or replacement on the marketplace was rejected
  struct RejectEventModel {
  
    // FIX::OrdRejReason
    // Values are
    //   const int OrdRejReason_UNKNOWN_SYMBOL = 1;
    //   const int OrdRejReason_EXCHANGE_CLOSED = 2;
    //   const int OrdRejReason_ORDER_EXCEEDS_LIMIT = 3;
    //   const int OrdRejReason_UNKNOWN_ORDER = 5;
    //   const int OrdRejReason_DUPLICATE_ORDER = 6;
    //   const int OrdRejReason_STALE_ORDER = 8;
    //   const int OrdRejReason_TRADE_ALONG_REQUIRED = 9;
    //   const int OrdRejReason_INVALID_INVESTOR_ID = 10;
    //   const int OrdRejReason_INCORRECT_QUANTITY = 13;
    //   const int OrdRejReason_UNKNOWN_ACCOUNT = 15;
    //   const int OrdRejReason_OTHER = 99;
    int status;
    
    // Details
    std::string message;
  
  };

  // -------- -------- -------- -------- -------- -------- -------- --------
  // MARK: Fill Event Model
  //
  // Fills are messages that report an order match, be it partial or
  // a complete fill

  struct FillEventModel {
    
    // Values are
    //   PartialFill
    //   CompleteFill
    std::string status;
    
    // ISIN or CUSIP (depending on setup)
    std::string securityCode;
        
    // ATS Execution Code
    std::string executionCode;
    
    // Who we will face
    std::string contraClearingMpid;

    // Optionally a clearing account
    std::string contraClearingAccount;

    // Where it executed (for now always OYLD)
    std::string executedBy;
    
    // Values are
    //   Buy
    //   Sell
    std::string side;

    // How much was filled
    double fillQuantity;
    
    // At what price
    double fillPrice;

    // At what yield
    double fillYield;

    // What the ATS knows as remaining
    double remainingQuantity;
    
    // Cash block
    double principal;
    
    double accrued;
    
    double settlementAmount;
    
    // Settlement date in ISO Date format
    std::string settlementDate;
    
    // Cumulative quantity for all fills on this order
    double cumulativeQuantity;
    
    // Average price for all fills on this order
    double averagePrice;
    
    // When the ATS executed (UTC Timestamp)
    std::string executedAt;
  };
  
  // -------- -------- -------- -------- -------- -------- -------- --------
  // MARK: Post Trade Event Model
  //
  // Post Trade Events are messages that cancel or correct a
  // fill after the order is completed. They should only occur
  // under rare and exceptional circumstances

  struct PostTradeEventModel {
  
    // Values are
    //   Cancel
    //   Correct
    std::string status;
        
    // ATS Execution Code
    std::string executionCode;
    
    // If status == correct, these are set
    double quantity { 0.0 };
    
    double price { 0.0 };
    
    double yield { 0.0 };
    
    double principal { 0.0 };
    
    double accrued { 0.0 };
    
    double settlement { 0.0 };
  };
  
  // -------- -------- -------- -------- -------- -------- -------- --------
  // MARK: Execution Event Model
  
  struct ExecutionEventModel
  {
    // Against which order
    std::string orderCode;
    
    // Payload
    std::variant<
      AcknowledgeEventModel,
      RejectEventModel,
      FillEventModel,
      PostTradeEventModel
    > value;
  };
  
  // -------- -------- -------- -------- -------- -------- -------- --------
  // MARK: Execution Event Codec

  class ExecutionEventCodec
  {
  
    public:
    
      std::optional<ExecutionEventModel> onExecutionReport(
        const FIX44::ExecutionReport& message
      ) const;

    private:
    
      Log log_;
  
  };

} // Namespace FixClient
