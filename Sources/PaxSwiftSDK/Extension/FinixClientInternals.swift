//
//  FinixClientInternals.swift
//  FinixPOS
//
//  Created by Jack Tihon on 4/7/20.
//  Copyright © 2020 Finix Payments, Inc. All rights reserved.
//

import Foundation

extension FinixClient {
    private var isSandbox: Bool {
        config.environment == .Sandbox || config.environment == .QA
    }

    typealias MerchantRequestCompletion = (FinixAPIResponse.MerchantsResponse?, Error?) -> Void
    /// Fetch merchant information
    /// - Parameters:
    ///   - merchant: merchant id
    ///   - completion: merchant response
    func merchantsRequest(merchant: MerchantId, completion: @escaping MerchantRequestCompletion) {
        let path = "merchants/\(merchant)"
        finixRequest(path: path, completion: completion)
    }

    typealias DeviceProcessorDetailsRequestCompletion = (FinixAPIResponse.DeviceProcessorDetail?, Error?) -> Void
    func deviceProcesserDetailsRequest(deviceId: String, completion: @escaping DeviceProcessorDetailsRequestCompletion) {
        let path = "devices/\(deviceId)/device_processor_details"
        finixRequest(path: path, completion: completion)
    }

    typealias IdentityRequestCompletion = (FinixAPIResponse.Identity?, Error?) -> Void
    func identityRequest(for identity: FinixAPIResponse.IdentityId, completion: @escaping IdentityRequestCompletion) {
        let path = "identities/\(identity)"
        finixRequest(path: path, completion: completion)
    }

    // this makes an API call (GET with no parameters) to the path and invokes the completion handler with either the decoded response or Error.
    func finixRequest<ResponseType: Decodable>(path: String, completion: @escaping (ResponseType?, Error?) -> Void) {
        guard let url = URL(string: path, relativeTo: endpoint) else {
            let error = FinixError(code: .MalformedRequest, message: "Could not encode path!")
            completion(nil, error)
            return
        }

        let request = URLRequest(url: url, method: .GET)

        finixRequest(request: request, completion: completion)
    }

    // Generic form of finixRequest where a request is passed in
    func finixRequest<ResponseType: Decodable>(request: URLRequest, completion: @escaping (ResponseType?, Error?) -> Void) {
        logger.http(request: request)
        let task = session.dataTask(with: request) { data, response, error in
            guard let data = data else {
                completion(nil, error)
                return
            }

            guard let response = response as? HTTPURLResponse else {
                completion(nil, error)
                return
            }

            guard response.statusCode >= 200, response.statusCode < 300 else {
                // we have a problem. let upstream know it was an http status problem
                self.logger.debug("response statusCode = \(response.statusCode)")
                let error = FinixError(code: .RequestFailed(response.statusCode),
                                       message: String.localizedStringWithFormat(
                                           NSLocalizedString("Request failed with status %d", comment: "Finix API Request failed"),
                                           response.statusCode
                                       ))
                self.logger.http(error: error)
                completion(nil, error)
                return
            }

            let decoder = JSONDecoder()
            decoder.dateDecodingStrategy = .formatted(.finixISO8601)
            self.logger.http(response: response)
            if self.isSandbox {
                self.logger.http(responseData: data)
            }

            guard let decoded = try? decoder.decode(ResponseType.self, from: data) else {
                let error = FinixError(code: .CannotDecodeResponse, message: "Can't decode \(ResponseType.self) response")
                self.logger.http(error: error)
                completion(nil, error)
                return
            }
            self.logger.http(decoded)
            completion(decoded, nil)
        }

        task.resume()
    }

    // GET /transfers/:transferId

    typealias TransferResponseHandler = (FinixOperation.TransferResponse?, Error?) -> Void
    func getTransfer(transferId: TransferId, completion: @escaping TransferResponseHandler) {
        guard let url = URL(string: "transfers/\(transferId)", relativeTo: endpoint) else {
            let error = FinixError(code: .MalformedRequest, message: "Could not encode path!")
            completion(nil, error)
            return
        }

        let request = URLRequest(url: url, method: .GET)

        finixRequest(request: request) { (response: FinixOperation.TransferResponse?, error: Error?) in
            guard let response = response else {
                completion(nil, error)
                return
            }

            guard CurrencyCode(iso: response.currencyCode) == CurrencyCode.USD else {
                let error = FinixError(code: .InvalidCurrencyCode, message: "Expected \(CurrencyCode.USD.isoCode) but got \(response.currencyCode) instead.")
                completion(nil, error)
                return
            }
            completion(response, nil)
        }
    }
}
