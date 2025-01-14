//
//  View+Ext.swift
//  PaxSwiftSDKDemo
//
//  Created by Tom Nguyen on 1/13/25.
//

import SwiftUI

extension View {
    func hideKeyboard() {
        UIApplication.shared.sendAction(#selector(UIResponder.resignFirstResponder),
                                        to: nil,
                                        from: nil,
                                        for: nil)
    }
}
