//
//  FinixError.swift
//  FinixPOS
//
//  Created by Jack Tihon on 3/29/20.
//  Copyright © 2020 Finix Payments, Inc. All rights reserved.
//

import Foundation

/// Errors from the Finix SDK
public struct FinixError: Error {
    /// initializer for internal errors
    /// - Parameter code: `Code`
    /// - Parameter message: error message
    init(code: Code, message: String) {
        self.code = code
        self.message = message
    }

    /// the error code
    public let code: Code

    /// the message associated with the error
    public let message: String

    /// error code
    public enum Code {
        // Finix API Errors

        /// The card was declined for an unknown reason. The cardholder needs to contact their issuer for more information.
        case GenericDecline

        /// The card has expired. The cardholder needs to use another card that's not expired.
        case ExpiredCard

        /// A transaction with the same amount and card was approved recently and marked as a duplicate. If this duplicate transaction was intentional, set check_for_duplicate_transactions to false.
        case DuplicateTransaction

        /// The card has been reported as lost or stolen by the cardholder. The cardholder needs to contact their issuing bank.
        case PickUpCard

        /// The card was declined for an unknown reason. The cardholder needs to contact their card issuer for more information.
        case CallIssuer

        /// The transaction is not permitted by the issuing bank. The cardholder needs to contact their issuing bank for more information.
        case InvalidTransaction

        /// The amount exceeds the amount that is allowed on the card. The cardholder needs to check with their issuing bank to see if they can make purchases of that amount.
        case InvalidAmount

        /// The card number is not valid. The cardholder needs to contact their issuing bank for more information or use another card.
        case InvalidAccountNumber

        /// The card has a restriction preventing approval for this transaction. Please contact the issuing bank for a specific reason.
        case RestrictedCard

        /// The transaction was declined because the card type is not permitted. The cardholder needs to use a different type of card.
        case TransactionNotPermitted

        /// There was a network communication error with the host. Check your network connection and retry the transaction.
        case CommunicationError

        /// Unknown
        case Unknown

        /// SDK is not initialized
        case SDKNotInitialized

        /// Reader not connected
        case CardReaderNotConnected

        /// Cannot encode request parameters
        case CannotEncodeParameters

        /// Response was not recognized
        case CannotDecodeResponse

        /// Request was malformed
        case MalformedRequest // request was malformed
        // TODO: should a failed request also include the request URL?

        /// Request failed with status
        case RequestFailed(_ statusCode: Int) // when an api request fails, pass along the error

        /// Transaction Error. Contains detailed reason with ``TransactionStatus``
        case TransactionError(_: TransactionStatus)

        /// Initialization failure
        case InitializationError

        /// Failed to parse authorization response
        case FailedToParseAuthorizationResponse

        /// Authorization failure with detail
        case AuthorizationFailure(_ error: Error) // TODO: should it just return the error?

        /// Authorization failure due to missing response
        case AuthorizationFailureMissingResponse

        /// Refund request failed
        case RefundRequestFailed

        /// Refund request failed with detail
        case RefundRequestFailedWithError(_ error: Error)

        /// Reader input error
        case CardInputError

        /// Invalid currency code
        case InvalidCurrencyCode // wrong currency

        /// No card data
        case NoCardData

        /// Card not accepted by terminal
        case BadCard

        /// When a Transfer operation has failed it will return the transaction status and the response for further processing.
        case TransferError(status: TransactionStatus, response: TransferResponse) // TODO: include more detail
    }

    /// This is returned when the SDK is not ready to be used
    static let SDKNotInitializedError = FinixError(code: .SDKNotInitialized, message: NSLocalizedString("SDK not initialized!", comment: "Error raised when SDK has not been initialized"))

    static let NoCardReaderError = FinixError(code: .CardReaderNotConnected, message: NSLocalizedString("No card reader connected", comment: "Error when no card reader is connected"))
}
