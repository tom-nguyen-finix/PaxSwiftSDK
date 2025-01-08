//
//  FinixError+VTPTransactionStatus.swift
//  FinixPOS
//
//  Created by Jack Tihon on 5/22/20.
//  Copyright © 2020 Finix Payments, Inc. All rights reserved.
//

import Foundation

/// Card Debit `TransactionError` reasons
/// Reference: ``FinixError``
public enum TransactionStatus: Int {
    /// Unknown
    case unknown = 0
    /// Approved
    case approved
    /// Partially Approved
    case partiallyApproved
    /// Approved Except Cashback
    case approvedExceptCashback
    /// Approved by Merchant
    case approvedByMerchant
    /// Call Issuer
    case callIssuer
    /// Declined
    case declined
    /// Needs to be Reversed
    case needsToBeReversed
}
