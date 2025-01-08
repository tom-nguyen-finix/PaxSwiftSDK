//
//  APICredentialsTests.swift
//  PaxMposSDK-UnitTests
//
//  Created by Fraser Moore on 5/29/24.
//

#warning("TODO: Migrate to PaxSwiftSDK's local test target")
import XCTest
@testable import PaxSwiftSDK

final class APICredentialsTests: XCTestCase {
    func testAuthorizationHeader() {
        let credentials = Finix.APICredentials(username: "testuser", password: "password")
        XCTAssertEqual(credentials.authorizationHeader, "Basic dGVzdHVzZXI6cGFzc3dvcmQ=")        
    }
}
