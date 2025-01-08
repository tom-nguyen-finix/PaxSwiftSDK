//
//  FinixClient+CardReader.swift
//  PaxMposSDK
//
//  Created by Jack Tihon on 5/5/24.
//

import Foundation

public extension FinixClient {
    func updateCardReaderFiles(_ statusCallback: DownloadStatusCallback?) {
        paxManager.downloadFiles(statusCallback)
    }

    // NOTE: not called `Type`
    enum TransactionType: String, Encodable {
        case sale = "SALE"
        case auth = "AUTHORIZATION"
        case refund = "REFUND"
    }

    // response from card reader transfer request
    /**
     {
         "amount": 8080,
         "amountRequested": 8080,
         "applicationId": null,
         "approvalCode": "381730",
         "bin": null,
         "brand": "MASTERCARD",
         "createdAt": null,
         "emvResponse": null,
         "failureCode": null,
         "failureMessage": null,
         "id": null,
         "lastFour": null,
         "maskedAccountNumber": "541333*******0102",
         "merchantAddress": null,
         "merchantId": null,
         "merchantName": null,
         "source": null,
         "state": "SUCCEEDED",
         "traceId": "FNXsUxiC659QnkL8ZjvpwRSeL",
         "updatedAt": null
     }

     {"trace_id":"FNXqhUu2NTNfkXcV3JnDNBZC5",
     "amount":1234,
     "amount_requested":1234,
     "masked_account_number":"554103*******4422",
     "brand":"MASTERCARD",
     "emv_response":null,
     "approval_code":null,
     "failure_code":"CALL_ISSUER",
     "failure_message":"The card was declined for an unknown reason. The cardholder needs to contact their card issuer for more information.",
     "state":"FAILED",
     "surcharge_amount":0,
     "tip_amount":0}
     */
    struct CardReaderTransferResponse: Decodable {
        public let amount: Int
        public let amountRequested: Int
        public let approvalCode: String?
//        let bin: ?
        public let brand: String
//        let createdAt: ?
        let emvResponse: String?
        let failureCode: String?
        let failureMessage: String?
        public let id:String?
        // let lastFour: ?
        public let maskedAccountNumber: String
//        let merchantAddress:?
//        let merchantId: ?
//        let merchantName: String?
        public let state: Transfer.State
        public let traceId: TraceId
//        let updatedAt: ?
        // tip_amount: Int
        // surcharge_amout: Int

        private enum CodingKeys: String, CodingKey {
            case amount
            case amountRequested = "amount_requested"
            case approvalCode = "approval_code"
            case brand
            case failureCode = "failure_code"
            case failureMessage = "failure_message"
            case maskedAccountNumber = "masked_account_number"
            case state
            case traceId = "trace_id"
            case emvResponse = "emv_response"
            case id
        }
    }

    typealias TransactionCompleteHandler = (CardReaderTransferResponse?, Error?) -> Void

    /**
     process a card transaction

     will read the card and

     */
    func startTransaction(amount: Currency, type transactionType: TransactionType, transactionHandler: TransactionCompleteHandler?) {
        /**
         create transaction by:
         - connect to reader
         - read card
         - extract track2
         - get card type
         - request tags from card type

         - post data to endpoint
         */
        paxManager.doTransaction(amount: amount) { [self] inputType, cardDetails, error in
            self.logger.info("\(String(describing: error)) \(String(describing: cardDetails))")
            guard let cardDetails else {
                guard let error else {
                    // return error when no deatils and no error
                    logger.error("Missing Card Details. got error", String(describing: error))
                    let error = FinixError(code: .NoCardData, message: "Missing Card Details")
                    transactionHandler?(nil, error)
                    return
                }

                if let error = error as? FinixError {
                    transactionHandler?(nil, error)
                } else {
                    logger.error("Missing Card Details. got error", error)
                    let missingCardError = FinixError(code: .NoCardData, message: "Missing Card Details")
                    transactionHandler?(nil, missingCardError)
                }
                return
            }

            guard let inputType = inputType else {
                logger.error("no input type error:\(String(describing: error))")
                let missingInputTypeError = FinixError(code: .NoCardData, message: "Missing Card Details")
                transactionHandler?(nil, missingInputTypeError)
                return
            }

            // call Finix card reader endpoint
            cardReaderTransfer(amount: amount, type: transactionType, inputType: inputType, cardDetails: cardDetails) { transferResponse, error in
                guard let transferResponse = transferResponse else {
                    transactionHandler?(nil, error)
                    return
                }
                self.logger.info("got transferResponse: ", transferResponse, "with error: \(String(describing: error))")
                transactionHandler?(transferResponse, error)
            }
        }
    }
}
