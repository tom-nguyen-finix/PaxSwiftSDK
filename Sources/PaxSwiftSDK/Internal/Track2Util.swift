//
//  Track2Util.swift
//  PaxMposSDK
//
//  Created by Jack Tihon on 5/4/24.
//

import Foundation

internal struct Track2Data: Equatable {
    let cardNumber: String
    let expiryDate: String
    let serviceCode: String
    let sanitizedTrack2: String
}

enum Track2Util {
    // parse track2
    static func parseTrack2(_ track2: String) -> Track2Data {
        let isSwipe: Bool = track2.contains("=")

        if isSwipe {
            var track2 = track2

            // remove header. aka starting ';'
            if track2.first == ";" {
                track2 = String(track2.dropFirst())
            }
            // swipe has an "="
            if track2.last == "?" {
                track2 = String(track2.dropLast())
            }

            // remove trailing ? if pr
            let split = track2.split(separator: "=")

            if split.count == 3 {
                // return the 3 parts
                let cardNumber = String(split[0])
                let expiry = String(split[1])
                let serviceCode = String(split[2])
                return Track2Data(cardNumber: cardNumber, expiryDate: expiry, serviceCode: serviceCode, sanitizedTrack2: track2)
            } else if split.count == 2 {
                let cardNumber = String(split[0])
                // YYMM for expiry
                let rest = split[1]
                let expiry = String(rest.prefix(4))
                let serviceCodeStartIndex = rest.index(rest.startIndex, offsetBy: 4)
                let serviceCode = String(rest[serviceCodeStartIndex...])
                return Track2Data(cardNumber: cardNumber, expiryDate: expiry, serviceCode: serviceCode, sanitizedTrack2: track2)
            }

            // oops. this is unexpected
            debugPrint("OOPS. Swipt Unexpected split \(split.count) — data:[\(track2)]")
            /**
             https://en.wikipedia.org/wiki/ISO/IEC_7813#Track_2
             Track 2 can store up to 40 numeric or special characters; it uses a lower density magnetic encoding than Track 1 but a more compact character encoding. ISO 7813 specifies the following structure for track 2 data:[2]

             SS : Start sentinel ";"
             PAN : Primary Account Number, up to 19 digits, as defined in ISO/IEC 7812-1
             FS : Field separator "="
             ED : Expiration date, YYMM or "=" if not present
             SC : Service code, 3 digits or "=" if not present
             DD : Discretionary data, balance of available digits
             ES : End sentinel "?"
             LRC : Longitudinal redundancy check, calculated according to ISO/IEC 7811-2
             */
            // example track2 from a swipe:
            // "4895281000000006=251210100000109?"

            return Track2Data(cardNumber: "TODO", expiryDate: "TODO", serviceCode: "TODO", sanitizedTrack2: "TODO")
        } else {
            // NOTE: contactless has a "d" and "f" for padding to whole byte
            /**
             https://emvlab.org/emvtags/?number=57
             Contains the data elements of track 2 according to ISO/IEC 7813, excluding start sentinel, end sentinel, and Longitudinal Redundancy Check (LRC), as follows: Primary Account Number (n, var. up to 19) Field Separator (Hex 'D') (b) Expiration Date (YYMM) (n 4) Service Code (n 3) Discretionary Data (defined by individual payment systems) (n, var.) Pad with one Hex 'F' if needed to ensure whole bytes (b)
             */
            // from emv -- NOTE the `d` delimiter
            // "4147400200527669d27092011020008500041f"

            var track2 = track2

            // strip off trailing 'f'
            if track2.last == "f" {
                track2 = String(track2.dropLast())
            }

            // split along delimiter
            let split = track2.split(separator: "d")

            let uppercasedTrack2 = track2.replacingOccurrences(of: "d", with: "D")

            if split.count == 3 {
                let cardNumber = String(split[0])
                let expiry = String(split[1])
                let serviceCode = String(split[2])
                return Track2Data(cardNumber: cardNumber, expiryDate: expiry, serviceCode: serviceCode, sanitizedTrack2: uppercasedTrack2)
            } else if split.count == 2 {
                let cardNumber = String(split[0])
                // YYMM for expiry
                let rest = split[1]
                let expiry = String(rest.prefix(4))
                let serviceCodeStartIndex = rest.index(rest.startIndex, offsetBy: 4)
                let serviceCode = String(rest[serviceCodeStartIndex...])
                return Track2Data(cardNumber: cardNumber, expiryDate: expiry, serviceCode: serviceCode, sanitizedTrack2: uppercasedTrack2)
            }

            // oops. this is unexpected
            debugPrint("OOPS. Unexpected split \(split.count)")

            return Track2Data(cardNumber: "TODO", expiryDate: "TODO", serviceCode: "TODO", sanitizedTrack2: "TODO")
        }
    }
}
