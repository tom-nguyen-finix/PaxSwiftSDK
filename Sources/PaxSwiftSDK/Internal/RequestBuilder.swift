//
//  RequestHelpers.swift
//  FinixPOS
//
//  Created by Jack Tihon on 4/7/20.
//  Copyright © 2020 Finix Payments, Inc. All rights reserved.
//

import Foundation

// URLRequest helpers
enum HTTPMethod: String {
    case GET
    case POST
    case PATCH
    case PUT
}

extension URLRequest {
    init(url: URL, method: HTTPMethod) {
        self.init(url: url)
        httpMethod = method.rawValue
        addValue("application/json", forHTTPHeaderField: "Content-Type")
    }
}

func requestBuilder<T: Encodable>(url: URL, method: HTTPMethod, payload: T) -> URLRequest? {
    var request = URLRequest(url: url, method: method)

    guard let jsonData = try? JSONEncoder().encode(payload) else {
        // TODO: how to notify that encoding failed?
        // let error = FinixError(code: .CannotEncodeParameters, message: "Cannot encode debit request parameters")
        return nil
    }
    request.httpBody = jsonData

    return request
}
