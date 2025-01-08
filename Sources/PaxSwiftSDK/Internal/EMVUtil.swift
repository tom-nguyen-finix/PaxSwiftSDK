//
//  EMVUtil.swift
//  PaxMposSDK
//
//  Created by Jack Tihon on 5/1/24.
//

import Foundation
import PaxEasyLinkControllerWrapper

// TLV Tag
struct EMVTag {
    enum TagValue: String {
        // NOTE: string values must be hex! and multiples of 2 so they can be encoded in UInt8
        case AID = "9F06"
        case PaxCardReadMethod = "0301"
        case swipeTrack2 = "0305"
        case swipeTrack1 = "0304"
        case PaxEMVContactlessTrack2 = "57"

        var tag: EMVTag {
            EMVTag(hexString: rawValue)!
        }
    }

    init?(hexString: String) {
        guard let hex = hexString.hexadecimal else {
            return nil
        }
        data = hex
    }

    let data: Data
}

// structure for holding EMV data read from the card
struct EMVData { // THIS IS FOR AID, which is tag "9F06"
    let data: Data
}

enum CardType: String {
    case visa // Visa
    case mastercard // Mastercard
    case amex // American Express
    case discover // Discover
    case unknown // Unknown card type
}

// Utilities for dealing with EMV and TLV data

enum EMVUtil {
    // return the type of card given the emv data
    static func cardType(from item: FinixTLVItem) -> CardType {
        assert(item.tlv.tag.hexadecimal.uppercased() == EMVTag.TagValue.AID.rawValue)
        let prefix = item.tlv.value.hexadecimal.uppercased().prefix(10)
        switch prefix {
        case "A000000003":
            return .visa
        case "A000000004",
             "A000000005":
            return .mastercard
        case "A000000025":
            return .amex
        case "A000000152",
             "A000000065",
             "A000000333",
             "325041592":
            return .discover
        default:
            return .unknown
        }
    }

    /// Tags to pull for each card type
    enum CardTypeTags {
        // TEST
        static let visa = [
            "9F02", "9F03", "9F26",
            "82",
            "9F36",
            "84", "9F10", "9F33", "9F1A",
            "95", "5F2A",
            "9A", "9C", "9F37",
            "9F5B", "C0", "9F27",
            "57",
            "5F34", "9F6E", "9F7C",
            "50", "9F12", "9F11",
        ]
        static let mastercard = [
            "9F02", "9F03", "9F26",
            "82",
            "9F36", "9F34", "9F27",
            "84", "9F10", "9F33", "9F1A",
            "95", "5F2A",
            "9A", "9C", "9F37",
            "57", "DF21", "9F09", "DF12", "9F1D",
            "5F34",
            "50", "9F12", "9F11",
        ]
        static let americanExpress = [
            "9F02", "9F03", "9F26",
            "82", "5F34",
            "9F36", "9F27", "9F10", "9F1A",
            "95", "5F2A",
            "9A", "9C", "9F37",
            "57", "9F06",
            "50", "9F12", "9F11",
        ]
        static let discover = [
            "9F02", "9F03", "9F26", "9F06",
            "82",
            "9F36", "9F09", "9F27",
            "84", "9F1E", "9F10", "9F33",
            "9F1A", "9F35",
            "95", "5F2A",
            "9A", "9F41", "9C", "9F37", "DF3F", "9F5B",
            "57", "5F34", "9F6E",
            "50", "9F12", "9F11",
        ]
    }

    static func cardTags(for cardType: CardType) -> [String] {
        switch cardType {
        case .visa:
            return CardTypeTags.visa
        case .mastercard:
            return CardTypeTags.mastercard
        case .amex:
            return CardTypeTags.americanExpress
        case .discover:
            return CardTypeTags.discover
        case .unknown:
            return CardTypeTags.visa // default. is this correct?
        }
    }
}

// MARK: Tags and TLV

func convert(_ tags: [EMVTag]) -> Data {
    var data = Data()
    tags.forEach {
        data.append($0.data)
    }
    return data
}

// TLV
struct FinixTLVItem {
    init(_ tlvItem: TlvItem) {
        tlv = tlvItem
    }

    let tlv: TlvItem
}

// convert from FinixTLVItem to form expected by setData()
func convert(_: [FinixTLVItem]) -> Data {
    // pack into a byte array
    Data()
}

func convert(from tlvArray: NSArray?) -> [FinixTLVItem] {
    guard let array = tlvArray as? [TlvItem] else {
        // TODO: error
        return []
    }

    return array.map { FinixTLVItem($0) }
}
