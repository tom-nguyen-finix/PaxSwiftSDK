//
//  RequestResponse.swift
//  FinixPOS
//
//  Created by Jack Tihon on 4/7/20.
//  Copyright © 2020 Finix Payments, Inc. All rights reserved.
//

import Foundation

/// an identifer for tracking a transaction
/// NOTE: most of responses have a `traceId`
public typealias TraceId = String
public typealias TransferId = String
public typealias SourceId = String // Identifier for a payment Source
public typealias AuthorizationId = String

/// FinixClient Request and Response payloads
/// This file contains the request and response payloads for the SDK.

// NOTE: Tags must be a String to String mapping. If it does not conform tags will not come back.
/// Custom Resource Tags in a `[String:String]` mapping
/// - Reference: [API Fundamentals: Tags](https://developers.finixpayments.com/apis/api-fundamentals/tags/)
public typealias ResourceTags = [String: String]

/// Debit Response from `updateTransfersRecord()`
public struct DebitResponse: TransferResponse {
    public let id: TransferId
    /// - NOTE:: see `TransferState`
    /// - TODO: Update state to an enum

    /// Transfer state
    public let state: Transfer.State
    /// TraceId
    public let traceId: TraceId

    /// ID of the Payment Instrument where funds get debited.
    public let source: SourceId?

    /// amount debited
    public let amount: Currency
    /// Optional custom tags
    public let tags: ResourceTags? /// Optional custom tags
}

/// Request payload for `sale and authorization`
/// - Reference: ``FinixClient/cardSale(_:completion:)``
/// - Reference: ``FinixClient/cardAuthorization(_:completion:)``
public struct TransferRequest {
    /// amount for the sale
    let amount: Currency

    /// Optional custom tags
    let tags: ResourceTags?

    /// initializer
    public init(amount: Currency, tags: ResourceTags? = nil) {
        self.amount = amount
        self.tags = tags
    }
}

/****************
   VTPAuthorizationRequest

   VTPFinancialRequestBase
      let cardholderPresentCode: VTPCardHolderPresentCode
      let clerkNumber: String
      let laneNumber: String
      let referenceNumber: String
      let shiftID: String
      let ticketNumber: String

   VTPFinancialRequestAmounts
      let salesTaxAmount: Currency
      let transactionAmount: Currency

   VTPFinancialRequestConvenienceFeeAmount
      let convenienceFeeAmount: Currency

   VTPFinancialRequestTipAmount
      let tipAmount: Currency

   VTPAddressRequest
      let billingEmail: String
 ****************/

// VTPPaymentType
public enum PaymentType {
    case Unknown
    case Credit
    case Debit
    case GiftCard
    case EBT
}

// VTPEbtType
public enum EBTType {
    case NotSet
    case FoodStamps
    case CashBenefits
}

/// Helper protocol for checking response state
public protocol ResponseState {
    /// the response state from the server
    var state: Transfer.State { get }
    /// true if success
    var success: Bool { get }
    /// true if pending
    var pending: Bool { get }
}

/// helper to determing `success` and `pending` for responses with `state`
public extension ResponseState {
    /// true if success
    var success: Bool {
        state == .succeeded
    }

    /// true if pending
    var pending: Bool {
        state == .pending
    }
}

/// A Transfer represents any flow of funds either to or from a Payment Instrument (identified by `source`).
public protocol TransferResponse: ResponseState {
    var id: TransferId { get } // The ID of the Transfer resource.
    var traceId: TraceId { get } // Trace ID of the Transfer. The processor sends back the trace_id so you can track the Transfer end-to-end.
    var source: SourceId? { get } // The ID of the Payment Instrument that will be debited and performing the Transfer.
}
