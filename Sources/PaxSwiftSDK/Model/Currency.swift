//
//  Currency.swift
//  FinixPOS
//
//  Created by Jack Tihon on 3/17/20.
//  Copyright © 2020 Finix Payments, Inc. All rights reserved.
//
import Foundation

/// Hold an amount in a specific currency
public struct Currency {
    /// amount in smallest unit of currency. e.g. Cents for USD
    public let amount: Int

    /// amount in decimal converted from the `amount`
    public var decimal: Decimal {
        switch code {
        case .USD:
            return Decimal(sign: .plus, exponent: -2, significand: Decimal(amount))
        }
    }

    /// the currency code
    public let code: CurrencyCode

    /// Initialize with Decimal amount and `CurrencyCode`
    /// - parameter amount: decimal amount e.g. `3.14`
    /// - parameter currencyCode: currency
    public init(decimal: Decimal, code: CurrencyCode) {
        switch code {
        case .USD:
            amount = ((decimal * 100) as NSDecimalNumber).intValue
        }

        self.code = code
    }

    /// Initialize with smallest unit (e.g. cents for USD) and `CurrencyCode`
    /// - parameter magnitude: amount in the smallest unit. e.g. `314` would be used for $3.14 USD
    /// - parameter code: `CurrencyCode`
    public init(amount: Int, code: CurrencyCode) {
        switch code {
        case .USD:
            self.amount = amount
        }
        self.code = code
    }
}

extension Currency: Equatable {}

extension Currency: CustomDebugStringConvertible {
    public var debugDescription: String {
        "Currency(\(decimal) \(code))"
    }
}

/// An enum to hold the supported currency codes needed by Currency
/// - Note: Only `USD` is supported at this time.
public enum CurrencyCode {
    /// US Dollar
    case USD

    /// initialize with an ISO currency code
    /// - parameter: iso: an ISO currency identifier
    init(iso: String) {
        let iso = iso.uppercased()
        switch iso {
        case CurrencyCode.USD.isoCode:
            self = .USD
        default:
            fatalError("Unhandled currency code: \(iso)")
        }
    }

    /// the corresponding ISO currency code
    var isoCode: String {
        switch self {
        case .USD:
            return "USD"
        }
    }
}
