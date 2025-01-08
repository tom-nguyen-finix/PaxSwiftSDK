//
//  FinixClient+PaxManagerDelegate.swift
//  PaxMposSDK
//
//  Created by Jack Tihon on 5/4/24.
//

import Foundation

extension FinixClient: PaxManagerDelegate {
    func promptForCard(manager _: PaxManager, prompt: String) {
        DispatchQueue.main.async {
            self.interactionDelegate?.onDisplayText(prompt)
        }
    }

    func didReadCard(manager _: PaxManager, prompt: String) {
        DispatchQueue.main.async {
            self.interactionDelegate?.onDisplayText(prompt)
        }
    }
}
