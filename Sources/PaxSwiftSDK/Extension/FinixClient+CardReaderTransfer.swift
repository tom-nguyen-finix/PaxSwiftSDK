//
//  FinixClient+CardReaderTransfer.swift
//  PaxMposSDK
//
//  Created by Jack Tihon on 5/5/24.
//

import Foundation

extension FinixClient {
    /// Send the Pax card reader payload as a transfer
    /// - Parameters:
    ///     - transfer : card reader payload
    ///     - completion: the handler will be called when complete
    /// - Note: The completion will be delivered on the main thread
    /// - Reference: (Card Orchestration Transfer)[https://developers.finixpayments.com/]
    func cardReaderTransfer(amount: Currency, type transactionType: TransactionType, inputType: PaxManager.CardInputType, cardDetails: CardDetails, completion: TransactionCompleteHandler?) {
        // Deliver the completion on the main thread to prevent a class of errors
        let mainCompletion: TransactionCompleteHandler = { transfer, error in
            if let error = error {
                self.logger.error("cardReaderTransfer failed with error:\(error)")
            }

            switch transfer?.state {
            case .succeeded:
                print("Succeeded Online Result: \(transfer?.emvResponse ?? "Null Value 030801018A023030 030801008A023030")")

                let _ = self.handleEMVConfigurationResponse("03080100")
                let _ = self.handleEMVResponse(transfer?.emvResponse ?? "8A023030")
            case .failed:
                print("Failed Online Result: \(transfer?.emvResponse ?? "Null Value 030801018A023030")")

                let _ = self.handleEMVConfigurationResponse("03080101")
                let _ = self.handleEMVResponse(transfer?.emvResponse ?? "8A023030")
            default:
                print("Failed Offline Result: 03080102")

                let _ = self.handleEMVConfigurationResponse("03080102")
            }

            let ret = self.paxManager.completeTransaction()
            print(ret)

            DispatchQueue.main.async {
                completion?(transfer, error)
            }
        }

//        guard let laneId = laneId else {
//            // TODO: add extra message about missing laneId
//            mainCompletion(nil, FinixError.SDKNotInitializedError)
//            return
//        }

        guard isReaderConnected() == true else {
            mainCompletion(nil, FinixError.NoCardReaderError)
            return
        }
       /// `Note-` When the transaction type will be auth, the auth API will hit, same as android SDK.
        let endPoint = transactionType == FinixClient.TransactionType.auth ? "card_reader/authorizations" : "card_reader/transfers"
        guard let url = URL(string: endPoint, relativeTo: endpoint) else {
            let error = FinixError(code: .MalformedRequest, message: "Could not encode path!")
            mainCompletion(nil, error)
            return
        }

        guard let inputMethod = inputType.inputMethod else {
            let error = FinixError(code: .SDKNotInitialized, message: "No Input Method!")
            mainCompletion(nil, error)
            return
        }

        let parameters = FinixOperation.CardReader.TransferRequest(amount: amount.amount,
                                                                   currency: amount.code.isoCode,
                                                                   applicationId: "",
                                                                   deviceId: config.deviceId,
                                                                   merchantId: config.merchantId,
                                                                   serialNumber: connectedDevice?.name ?? "Unknown",
                                                                   failureDetails: nil,
                                                                   gateway: FinixAPIEndpoint.Gateway(config.environment),
                                                                   input: inputMethod,
                                                                   mid: config.mid,
                                                                   traceId: nil, // we don't set this
                                                                   transactionDateTime: String(Int(Date.timeIntervalSinceReferenceDate)),
                                                                   transactionType: transactionType,
                                                                   cardDetails: cardDetails)

        guard let request = requestBuilder(url: url, method: .POST, payload: parameters) else {
            let error = FinixError(code: .CannotEncodeParameters, message: "Cannot encode card transfer parameters")
            mainCompletion(nil, error)
            return
        }

        // TODO: decode CardReaderr.TransferResponse?
        finixRequest(request: request) { (response: CardReaderTransferResponse?, error: Error?) in
            print(response,error)
            guard let response = response else {
                mainCompletion(nil, error)
                return
            }
            mainCompletion(response, error)
        }
    }

    func handleEMVResponse(_ response: String) -> Bool {
        var failedTags: [EMVTag] = []
        return paxManager.setData(ofType: .transactionData, dataList: [response.hexadecimal!], tagList: &failedTags)
    }

    func handleEMVConfigurationResponse(_ response: String) -> Bool {
        var failedTags: [EMVTag] = []
        return paxManager.setData(ofType: .configurationData, dataList: [response.hexadecimal!], tagList: &failedTags)
    }
}
