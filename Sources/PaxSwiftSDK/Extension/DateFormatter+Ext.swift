//
//  DateFormatter+Ext.swift
//  PaxSwiftSDK
//
//  Created by Tom Nguyen on 1/7/25.
//

import Foundation

/// Finix Date Formatter
extension DateFormatter {
    static let finixISO8601: DateFormatter = {
        let formatter = DateFormatter()
        formatter.dateFormat = "yyyy-MM-dd'T'HH:mm:ss.SSZZZZZ"
        formatter.calendar = Calendar(identifier: .iso8601)
        formatter.timeZone = TimeZone(secondsFromGMT: 0)
        formatter.locale = Locale(identifier: "en_US_POSIX")
        return formatter
    }()
}
