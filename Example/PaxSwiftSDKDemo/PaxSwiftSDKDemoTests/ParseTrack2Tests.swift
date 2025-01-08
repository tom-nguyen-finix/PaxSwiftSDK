//
//  ParseTrack2Tests.swift
//  PaxMposSDK-UnitTests
//
//  Created by Jack Tihon on 5/4/24.
//
#warning("TODO: Migrate to PaxSwiftSDK's local test target")
import XCTest
@testable import PaxSwiftSDK

final class ParseTrack2Tests: XCTestCase {
    func testSwipeTrack2() throws {
        let testCases: [(track2: String, details: Track2Data)]  = [
            // 4895281000000006=251210100000109?
            ("4895281000000006=251210100000109?", .init(cardNumber: "4895281000000006", expiryDate: "2512", serviceCode: "10100000109", sanitizedTrack2: ""))
        ]
        
        testCases.forEach{ track2, expected in
            let result = Track2Util.parseTrack2(track2)
            XCTAssertEqual(result, expected, "expected!")
        }
    }

    func testEMVTrack2() throws {
        // 4147400200527669d2011020008500041f
        let testCases: [(track2: String, details: Track2Data)]  = [
            ("4147400200527669d27092011020008500041f", .init(cardNumber: "4147400200527669", expiryDate: "2709", serviceCode: "2011020008500041", sanitizedTrack2: ""))
        ]
        
        testCases.forEach{ track2, expected in
            let result = Track2Util.parseTrack2(track2)
            XCTAssertEqual(result, expected, "expected!")
        }
    }
}
