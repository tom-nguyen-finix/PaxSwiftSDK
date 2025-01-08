//
//  FinixClientDeviceInteractionDelegate.swift
//  PaxMposSDK
//
//  Created by Jack Tihon on 5/4/24.
//

import Foundation

/// Client will be notified of text to show the user and on card removal. E.g. when to insert/tap/swipe a card.
public protocol FinixClientDeviceInteractionDelegate: AnyObject {
    /// When text is to be shown to the user. e.g. "Insert, Tap or Swipe Card"
    /// - Parameter text: text to show the user
    func onDisplayText(_ text: String)

    /// Inform card removal
    func onRemoveCard()
}
