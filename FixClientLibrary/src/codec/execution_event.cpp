// -------- -------- -------- -------- -------- -------- -------- --------
//
// execution_event.cpp
// FixClientLibrary
//
// Copyright © 2024 OpenYield, Inc.
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.
//
// -------- -------- -------- -------- -------- -------- -------- --------

#include "codec/execution_event.hpp"

namespace FixClient {

	std::optional<ExecutionEventModel> ExecutionEventCodec::onExecutionReport(
    const FIX44::ExecutionReport& message) const
  {
    FIX::ClOrdID clOrdId;
    FIX::ExecType execType;
    FIX::OrdStatus ordStatus;
    FIX::NoPartyIDs noPartyIDs;
    FIX44::ExecutionReport::NoPartyIDs noPartiesGroup;
    FIX::PartyID partyId;
    FIX::PartyRole partyRole;

    message.get(clOrdId);
    message.get(execType);
    message.get(ordStatus);
    message.get(noPartyIDs);
  
    // -------- -------- -------- --------
    // MARK: Acknowledgements
    
    if (execType == FIX::ExecType_NEW) {
      if (ordStatus == FIX::OrdStatus_NEW) {
        AcknowledgeEventModel payload = {
          .status = "NewOrderAccepted"
        };
        
        return ExecutionEventModel {
          .orderCode = clOrdId,
          .value = payload
        };
      }
    }

    if (execType == FIX::ExecType_CANCELED) {
      if (ordStatus == FIX::OrdStatus_CANCELED) {
        std::string reason = "";
        if (message.isSetField(58)) {
          reason = message.getField(58);
        }
        
        AcknowledgeEventModel payload = {
          .status = "OrderCanceled",
          .reason = reason
        };
        
        return ExecutionEventModel {
          .orderCode = clOrdId,
          .value = payload
        };
      }
    }

    if (execType == FIX::ExecType_REPLACED) {
      if (ordStatus == FIX::OrdStatus_REPLACED) {
        AcknowledgeEventModel payload = {
          .status = "OrderReplaced"
        };
        
        return ExecutionEventModel {
          .orderCode = clOrdId,
          .value = payload
        };
      }
    }
    
    // -------- -------- -------- --------
    // MARK: Rejections
    
    if (execType == FIX::ExecType_REJECTED) {
      FIX::OrdRejReason ordRejReason;
      FIX::Text text;
      
      message.get(ordRejReason);
      message.get(text);
      
      RejectEventModel payload = {
        .status = ordRejReason,
        .message = text
      };
      
      return ExecutionEventModel {
        .orderCode = clOrdId,
        .value = payload
      };
    }
    
    // -------- -------- -------- --------
    // MARK: Fills (Partial & Complete)
    
    if (execType == FIX::ExecType_TRADE) {
    
      if ( ordStatus == FIX::OrdStatus_PARTIALLY_FILLED
        || ordStatus == FIX::OrdStatus_FILLED
      ) {
        FillEventModel payload;
        
        if (ordStatus == FIX::OrdStatus_PARTIALLY_FILLED) {
          payload.status = "PartialFill";
        } else {
          payload.status = "CompleteFill";
        }
        
        // Get more fields for Fills
        FIX::ExecID execId;
        FIX::SecurityID securityId;
        FIX::ClOrdID clOrdId;
        FIX::Side side;
        FIX::LastQty lastQty;
        FIX::LastPx lastPx;
        FIX::Yield yield;
        FIX::LeavesQty leavesQty;
        FIX::GrossTradeAmt grossTradeAmt;
        FIX::AccruedInterestAmt accruedInterestAmt;
        FIX::NetMoney netMoney;
        FIX::SettlDate settlDate;
        FIX::CumQty cumQty;
        FIX::AvgPx avgPx;
  //      FIX::TransactTime transactTime;
        
        message.get(execId);
        message.get(securityId);
        message.get(clOrdId);
        message.get(side);
        message.get(lastQty);
        message.get(lastPx);
        message.get(yield);
        message.get(leavesQty);
        message.get(grossTradeAmt);
        message.get(accruedInterestAmt);
        message.get(netMoney);
        message.get(settlDate);
        message.get(cumQty);
        message.get(avgPx);
  //      message.get(transactTime);
        
        payload.executionCode = execId;
        payload.securityCode = securityId;
        
        for (int i = 1; i <= noPartyIDs; i++) {
          message.getGroup(i, noPartiesGroup);
          noPartiesGroup.get(partyRole);
          
          if (partyRole == FIX::PartyRole_CONTRA_FIRM) {
            noPartiesGroup.get(partyId);
            payload.contraPartyCode = partyId;
          }

          if (partyRole == FIX::PartyRole_CONTRA_CLEARING_FIRM) {
            noPartiesGroup.get(partyId);
            payload.contraClearingCode = partyId;
          }

          if (partyRole == FIX::PartyRole_EXECUTING_FIRM) {
            noPartiesGroup.get(partyId);
            payload.executedBy = partyId;
          }
        }
        
        switch (side) {
          case FIX::Side_BUY:
            payload.side = "Buy";
            break;

          case FIX::Side_SELL:
            payload.side = "Sell";
            break;
        }
        
        payload.fillQuantity = lastQty;
        payload.fillPrice = lastPx;
        payload.fillYield = yield;
        payload.remainingQuantity = leavesQty;
        payload.principal = grossTradeAmt;
        payload.accrued = accruedInterestAmt;
        payload.settlementAmount = netMoney;
        payload.settlementDate = settlDate;
        payload.cumulativeQuantity = cumQty;
        payload.averagePrice = avgPx;
        payload.executedAt = message.getField(60);
        
        return ExecutionEventModel {
          .orderCode = clOrdId,
          .value = payload
        };
      }
    }
    
    // -------- -------- -------- --------
    // MARK: Post Trade
    
    if (execType == FIX::ExecType_TRADE_CANCEL) {
    
      FIX::ExecRefID execRefId;
      message.get(execRefId);

      PostTradeEventModel payload = {
        .status = "Cancel",
        .executionCode = execRefId
      };
      
      return ExecutionEventModel {
        .orderCode = clOrdId,
        .value = payload
      };
    }

    if (execType == FIX::ExecType_TRADE_CORRECT) {
    
      FIX::ClOrdID clOrdId;
      FIX::ExecRefID execRefId;
      FIX::LastQty lastQty;
      FIX::LastPx lastPx;
      FIX::Yield yield;
      FIX::GrossTradeAmt grossTradeAmt;
      FIX::AccruedInterestAmt accruedInterestAmt;
      FIX::NetMoney netMoney;
      
      message.get(clOrdId);
      message.get(execRefId);
      message.get(lastQty);
      message.get(lastPx);
      message.get(yield);
      message.get(grossTradeAmt);
      message.get(accruedInterestAmt);
      message.get(netMoney);
      
      PostTradeEventModel payload = {
        .status = "Cancel",
        .executionCode = execRefId,
        .quantity = lastQty,
        .price = lastPx,
        .yield = yield,
        .principal = grossTradeAmt,
        .accrued = accruedInterestAmt,
        .settlement = netMoney
      };
      
      return ExecutionEventModel {
        .orderCode = clOrdId,
        .value = payload
      };

    }

    log_.logCritic(
      "Execution Report Not Handled! " + message.toString()
    );
    
    // No event to return
    return std::nullopt;

  }
  
} // Namespace FixClient
