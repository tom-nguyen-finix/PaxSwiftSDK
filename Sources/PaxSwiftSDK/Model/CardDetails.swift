//
//  CardDetails.swift
//  PaxMposSDK
//
//  Created by Jack Tihon on 5/5/24.
//

import Foundation

/**
 emv
 Raw TLV dump of tags grabbed from card read. Tags we want vary by card network. Listed below.
 Ideally we remove any empty tags (tags with a value of 00)
 expiry
 Expiration date of the card in yymm
 Pull this from track 2 equivalent data or track 2; here’s the spec on track 2 data
 https://finixpayments.atlassian.net/wiki/spaces/~609d31fc8cbda700684a0bc9/pages/2402123801/Track+1+Track+2+Finix+Specification
 name
 Cardholder name pulled from 5F20 tag if available, otherwise from Track 1 (see spec linked above), else make it empty string “”
 track 1
 Track 1 data if available (only in swipes)
 track 2
 Track 2 data from swipe or value from Tag 57 (track 2 equivalent data). Mandatory
 */
// Payload to pass to server
struct CardDetails: Encodable {
    let name: String? = ""
    let cardNumber: String?
    let expiry: String?
    let cardHolderVerification: String? = "NO CVM"
    let emv: String?
    let track1: String?
    let track2: String? // NOTE: only take first 37 char?

    private enum CodingKeys: String, CodingKey {
        case name
        case cardNumber = "card_number"
        case expiry
        case cardHolderVerification = "card_holder_verification"
        case emv
        case track1
        case track2
    }
}
