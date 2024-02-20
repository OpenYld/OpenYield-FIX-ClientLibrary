// -------- -------- -------- -------- -------- -------- -------- --------
//
// order.hpp
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
//    │  FIX Order                                                    │░░
//    │                                                               │░░
//    │  - Create, Update or Cancel an Order                          │░░
//    │                                                               │░░
//    └───────────────────────────────────────────────────────────────┘░░
//      ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
//      ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
//
// -------- -------- -------- -------- -------- -------- -------- --------

#pragma once

#include <string>

#include "log.hpp"
#include "quickfix.hpp"
#include "../model/security_model.hpp"

namespace FixClient {

  // -------- -------- -------- -------- -------- -------- -------- --------
  // MARK: Order Action

  enum class OrderAction {

    New,
  
    Replace,
  
    Cancel

  };

  // -------- -------- -------- -------- -------- -------- -------- --------
  // MARK: Order Kind

  enum class OrderKind {

    Market,
  
    Limit
  
  };

  // -------- -------- -------- -------- -------- -------- -------- --------
  // MARK: Order Side

  enum class OrderSide {

    Buy,
  
    Sell
  
  };

  // -------- -------- -------- -------- -------- -------- -------- --------
  // MARK: Order Model

  struct OrderModel {

    OrderAction action;
    
    // Our order code
    std::string orderCode;

    // Original order ID
    std::string originalOrderCode;

    // Limit or Market
    OrderKind kind;
    
    // Who is placing the order
    std::string counterpartyCode;
    
    // Buy or Sell
    OrderSide side;
    
    // What
    SecurityModel security;
    
    // Current how much ordered
    double quantity;
    
    // Current Price
    double price;
    
  };
  
  // -------- -------- -------- -------- -------- -------- -------- --------
  // MARK: Order Dispatch
  
  class OrderDispatch
  {
    public:
    
      // Construct an order dispatch with the FIX TR sender comp ID
      OrderDispatch(const std::string& senderCompId);
    
      void sendOrder(const OrderModel& model);
      
      inline std::string senderCompId() const
      {
        return senderCompId_;
      }
    
    private:
    
      void sendNewOrder(const OrderModel& model);
      
      void sendReplaceOrder(const OrderModel& model);
      
      void sendCancelOrder(const OrderModel& model);
    
      std::string senderCompId_;
      Log log_;
    
  };


} // Namespace FixClient
