//
//  Data+Ext.swift
//  PaxSwiftSDK
//
//  Created by Tom Nguyen on 1/7/25.
//

import Foundation

extension Data {
    /// Hexadecimal string representation of `Data` object.
    var hexadecimal: String {
        map { String(format: "%02x", $0) }
            .joined()
    }
}
