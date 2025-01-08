//
//  FinixOperation.swift
//  FinixPOS
//
//  Created by Jack Tihon on 3/29/20.
//  Copyright © 2020 Finix Payments, Inc. All rights reserved.
//

import Foundation

// Transfer and Authorization states
// PENDING, FAILED, SUCCEEDED, CANCELED, UNKNOWN
internal enum TransferState: String, Encodable {
    case PENDING
    case FAILED
    case SUCCEEDED
    case CANCELED
    case UNKNOWN
}

// shared by finix api response
internal protocol BaseFinixResponse: Decodable {
    var state: Transfer.State { get }
    var traceId: TraceId { get } // Trace ID of the Transfer. The processor sends back the trace_id so you can track the Transfer end-to-end.
    var amount: Int { get } // this is in cents for USD e.g. 100 for $1.00 USD
    var currencyCode: String { get } // ISO 4217 3 letter currency code.
}

// Common Transfer fields
internal protocol BaseTransferResponse: BaseFinixResponse {
    var id: TransferId { get } //
    var source: SourceId? { get } // The ID of the Payment Instrument that will be debited and performing the Transfer.
}

// Common Authorization fields
internal protocol BaseAuthorizationResponse: BaseFinixResponse {
    var id: AuthorizationId { get }
    var source: SourceId { get }
}

// Encoding stuff in the actual Finix Request parameters
internal enum FinixOperation {
    // Operation key is passed into requests
    enum OperationKey: String, Codable {
        case CardPresentDebit = "CARD_PRESENT_DEBIT"
        case CardPresentAuthorization = "CARD_PRESENT_AUTHORIZATION"
        case CardPresentUnreferencedRefund = "CARD_PRESENT_UNREFERENCED_REFUND"
    }

    // A protocol for DebitTransfer and AuthorizationRequest
    struct TransferParameters: Encodable {
        let currency: String
        let amount: Int // this is in cents
        let device: String
        let operationKey: FinixOperation.OperationKey
        let tags: ResourceTags?

        enum CodingKeys: String, CodingKey {
            case currency
            case amount
            case device
            case operationKey = "operation_key" // TODO: this could also be done with a custom JSON encoding strategy, but probably not worth it
            case tags
        }
    }

    //////
    // Debit
    struct DebitTransferResponse: BaseTransferResponse, Decodable {
        let id: TransferId
        let state: Transfer.State
        let traceId: TraceId
        let source: SourceId?
        let amount: Int // this is in cents for USD e.g. 100 for $1.00 USD
        let currencyCode: String
        let tags: ResourceTags?
        let created: Date
        let updated: Date

        private enum CodingKeys: String, CodingKey {
            case id
            case state
            case traceId = "trace_id"
            case source
            case amount
            case currencyCode = "currency"
            case created = "created_at"
            case updated = "updated_at"
            case tags
        }
    }

    /// Transfer
    /// https://developers.finixpayments.com/#fetch-a-transfer
    /// GET
    struct TransferResponse: BaseTransferResponse, Decodable {
        let id: TransferId
        let state: Transfer.State
        let traceId: TraceId
        let source: SourceId?
        let amount: Int // this is in cents for USD e.g. 100 for $1.00 USD
        let currencyCode: String
        let tags: ResourceTags?
        let created: Date
        let updated: Date

        private enum CodingKeys: String, CodingKey {
            case id
            case state
            case traceId = "trace_id"
            case source
            case amount
            case currencyCode = "currency"
            case created = "created_at"
            case updated = "updated_at"
            case tags
        }

//        var debitResponse: DebitResponse {
//            let amount = Currency(amount: Decimal(self.amount), code: CurrencyCode(iso: currencyCode))
//            return DebitResponse(state: state, traceId: traceId, amount: amount, tags: tags)
//        }
    }

    //////
    // Auth

    struct PatchRawResponseRequest: Encodable {
        let rawResponse: String

        private enum CodingKeys: String, CodingKey {
            case rawResponse = "raw_response"
        }
    }

    typealias DebitRequestParameters = TransferParameters

    struct AuthorizationResponse: BaseAuthorizationResponse, Decodable { // TODO: share some fields with DebitResponse
        let id: AuthorizationId
        let state: Transfer.State
        let traceId: TraceId
        let source: SourceId
        let amount: Int
        let currencyCode: String
        let created: Date
        let updated: Date
        let tags: ResourceTags?

        private enum CodingKeys: String, CodingKey {
            case id
            case state
            case traceId = "trace_id"
            case source
            case amount
            case currencyCode = "currency"
            case created = "created_at"
            case updated = "updated_at"
            case tags
        }
    }

    struct UpdateTransactionResponse: BaseTransferResponse, Decodable {
        let id: TransferId
        let state: Transfer.State
        let traceId: TraceId
        let source: SourceId?
        let amount: Int
        let currencyCode: String
        let created: Date
        let updated: Date
        let tags: ResourceTags?

        private enum CodingKeys: String, CodingKey {
            case id
            case state
            case traceId = "trace_id"
            case source
            case amount
            case currencyCode = "currency"
            case created = "created_at"
            case updated = "updated_at"
            case tags
        }
    }

    typealias UpdateDebitResponse = UpdateTransactionResponse
    typealias UpdateAuthorizationResponse = UpdateTransactionResponse

    struct UnreferencedRefundResponse: BaseTransferResponse, Decodable {
        let id: TransferId
        let state: Transfer.State
        let traceId: TraceId
        let source: SourceId?
        let amount: Int
        let currencyCode: String
        let created: Date
        let updated: Date
        let tags: ResourceTags?

        private enum CodingKeys: String, CodingKey {
            case id
            case state
            case traceId = "trace_id"
            case source
            case amount
            case currencyCode = "currency"
            case created = "created_at"
            case updated = "updated_at"
            case tags
        }
    }

    typealias UpdateRefundResponse = UpdateTransactionResponse
    typealias RefundTransferResponse = TransferResponse

    // For capture
    struct CaptureRequest: Encodable {
        let amount: Int // The amount of the authorization you would like to capture in cents
        let tags: ResourceTags?

        private enum CodingKeys: String, CodingKey {
            case amount = "capture_amount"
            case tags
        }
    }

    typealias CaptureResponseHandler = (CaptureResponse?, Error?) -> Void
    struct CaptureResponse: BaseAuthorizationResponse, Decodable {
        // NOTE: this has both transferId and id...
        let id: AuthorizationId
        let state: Transfer.State
        let traceId: TraceId
        let source: SourceId
        let amount: Int
        let currencyCode: String
        let transferId: TransferId
        let deviceId: String
        let created: Date
        let updated: Date
        let tags: ResourceTags?

        private enum CodingKeys: String, CodingKey {
            case id
            case amount
            case traceId = "trace_id"
            case source
            case currencyCode = "currency"
            case state
            case transferId = "transfer"
            case deviceId = "device"
            case created = "created_at"
            case updated = "updated_at"
            case tags
        }
    }

    /**
     VOID
     **/

    // NOTE: this is a generic Void API response. It's up to you to distinguish between Authorization and Transfer
    // TODO: hide this from client and make a type-specific response like VoidAuthorizationResponse below.

    /// Void [transfers/authorizations]/<id>/record endpoint
    /// Note: this has captureAmount and rawResponse which is not present in the normal payload
    struct VoidTransferPayload: Codable {
        let captureAmount: Int
        let rawResponse: String
        private let void_me: Bool // should always be set to `true`

        private enum codingKeys: String, CodingKey {
            case captureAmount = "capture_amount"
            case rawResponse = "raw_response"
            case voidMe = "void_me"
        }

        init(amount: Currency, rawResponse: String) {
            // TODO: verify currencyCode
            captureAmount = amount.amount
            self.rawResponse = rawResponse
            void_me = true
        }
    }

    // For Void
    struct VoidAuthorizationRequest: Encodable {
        let voidMe: Bool

        private enum CodingKeys: String, CodingKey {
            case voidMe = "void_me"
        }
    }

    typealias VoidAuthorizationResponseHandler = (VoidAuthorizationResponse?, Error?) -> Void
    struct VoidAuthorizationResponse: BaseAuthorizationResponse, Decodable {
        let id: AuthorizationId
        let state: Transfer.State
        let traceId: TraceId
        let source: SourceId
        let amount: Int
        let currencyCode: String
        let created: Date
        let updated: Date
        let tags: ResourceTags?

        private enum CodingKeys: String, CodingKey {
            case id
            case state
            case traceId = "trace_id"
            case source
            case amount
            case currencyCode = "currency"
            case created = "created_at"
            case updated = "updated_at"
            case tags
        }
    }

    // For Refund
    struct RefundParameters: Encodable {
        let refundAmount: Int // The amount of the refund in cents (Must be equal to or less than the amount of the original Transfer)
        let deviceId: String

        private enum CodingKeys: String, CodingKey {
            case refundAmount = "refund_amount"
            case deviceId = "device"
        }
    }

    typealias RefundTransferResponseHandler = (RefundTransferResponse?, Error?) -> Void
}

extension FinixOperation {
    enum CardReader {
        /**
         input
         The way the card was red
         CARD_CONTACTLESS
         CARD_CHIP
         CARD_SWIPE
         */
        enum CardInputMethod: String, Encodable {
            case contactless = "CARD_CONTACTLESS"
            case chip = "CARD_CHIP"
            case swipe = "CARD_SWIPE"
        }

        /// card reader transfer request

        /** endopoint:
         https://cardpresent-orchestrator-http.qa.finixops.com/card_reader/transfers

         */
        /**
              {
             "amount": 8080,
             "applicationId": "",
             "cardDetails": {
                 "cardHolderVerification": "NO CVM",
                 "cardNumber": "5413330089020102",
                 "emv": "9F02060000000080809F03060000000000009F2608BD208AD4999544DD820259809F360200119F34031F03029F2701808407A00000000410109F101A0110A04203A40000000000000000000000FF00000000000000FF9F3303E008089F1A020124950500000080015F2A0201249A032403059C01009F3704807B2CCF9F090200029F1D082C008000000000005F34010150104D4153544552434152442044454249549F12104D4153544552434152442044454249549F110101",
                 "expiry": "2712",
                 "name": null,
                 "track1": null,
                 "track2": "5413330089020102D2712201150599110"
             },
             "currency": "USD",
             "deviceId": "DVssYUU613rqvyDjAXhcTCEU",
             "errorCode": "",
             "failureDetails": null,
             "gateway": "FINIX_V1",
             "input": "CARD_CONTACTLESS",
             "merchantId": "MUkRFuaGvFKB3X2YzbxQKx1Z",
             "mid": "7152a112-9254-476a-a760-85c7d295cc57",
             "serialNumber": "PBA3225632091",
             "traceId": null,
             "transactionDateTime": "1709687935",
             "transactionType": "SALE" || "AUTH" || "REFUND"
         }
              */
        struct TransferRequest: Encodable {
            let amount: Int
            let currency: String

            let applicationId: String
            let deviceId: String
            let merchantId: String

            let serialNumber: String // pass the local deviceId

            let failureDetails: String?

            let gateway: FinixAPIEndpoint.Gateway

            let input: CardInputMethod // "CARD_CONTACTLESS"

            // To be retrieved via GET request
            let mid: String

            // Should be null
            let traceId: TraceId?

            let transactionDateTime: String // unix epoch as string
            let transactionType: FinixClient.TransactionType // SALE, AUTH, or REFUND

            let cardDetails: CardDetails

            private enum CodingKeys: String, CodingKey {
                case amount
                case currency
                case applicationId = "application_id"
                case deviceId = "device_id"
                case merchantId = "merchant_id"
                case serialNumber = "serial_number"
                case failureDetails = "failure_details"
                case gateway
                case input
                case mid
                case traceId = "trace_id"
                case transactionDateTime = "transaction_date_time"
                case transactionType = "transaction_type"
                case cardDetails = "card_details"
            }
        } // transfer request
    } // extension CardReader
}
