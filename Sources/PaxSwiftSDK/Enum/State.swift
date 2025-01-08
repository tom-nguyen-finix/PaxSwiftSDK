//
//  State.swift
//  FinixPOS
//
//  Created by Jack Tihon on 1/11/22.
//

public enum Transfer {
    public enum State: Decodable, Equatable {
        case pending
        case failed
        case succeeded
        case canceled
        case unknown(value: String)

        public init(from decoder: Decoder) throws {
            let container = try decoder.singleValueContainer()
            let status = try? container.decode(String.self)
            switch status {
            case "PENDING": self = .pending
            case "FAILED": self = .failed
            case "SUCCEEDED": self = .succeeded
            case "CANCELED": self = .canceled
            default:
                self = .unknown(value: status ?? "unknown")
            }

            debugPrint("decoded state: \(self)")
        }
    }
}
