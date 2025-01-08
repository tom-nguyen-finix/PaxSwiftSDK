//
//  FinixConfig.swift
//  FinixPOS
//
//  Created by Jack Tihon on 4/7/20.
//  Copyright © 2020 Finix Payments, Inc. All rights reserved.
//
import Foundation

/// Configuration object passed to the SDK for initialization. It encodes everything needed to initialize the SDK.
public struct FinixConfig {
    /// - NOTE: the environment `.Sandbox` for tesing and `.Live` for production
    let environment: Finix.Environment

    /// - NOTE: authentication credentials
    let credentials: Finix.APICredentials

    /// - NOTE: the application descriptor
    let application: String

    /// - NOTE: the version of the consumer app
    let version: String

    /// - NOTE: the merchant's identifier
    let merchantId: String

    /// - NOTE: the merchant's mid
    let mid: String

    /// - NOTE: the type of device
    let deviceType: Finix.Device

    /// - NOTE: the Finix device identifier
    var deviceId: String

    /// - NOTE: If specified the card reader serial number. If nil it will connect to any compatible paired device.
    let serialNumber: String?

    /// this constructor requires all fields be defined
    /// - parameter environment: Sandbox or Live
    /// - parameter credentials: API authentication credentials
    /// - parameter application: The application descriptor
    /// - parameter version: The application version
    /// - parameter merchantId: The merchant identifier
    /// - parameter mid: The merchant mid
    /// - parameter deviceType: the type of the card reader. i.e. `BBPOS` or `Ingenico`
    /// - parameter serialNumber: Optional serial number for the card reader. If specified it will attempt connect only to the reader with the matching serial number.
    ///  Otherwise it will connect to any available paired device.
    public init(environment: Finix.Environment,
                credentials: Finix.APICredentials,
                application: String,
                version: String,
                merchantId: String,
                mid: String,
                deviceType: Finix.Device,
                deviceId: String,
                serialNumber: String? = nil) {
        self.environment = environment
        self.credentials = credentials
        self.application = application
        self.version = version
        self.merchantId = merchantId
        self.mid = mid
        self.deviceType = deviceType
        self.deviceId = deviceId
        self.serialNumber = serialNumber
    }
}

/// Namespace for config objects
public enum Finix {
    /// Type of card reader
    public enum Device {
        case Pax
    }

    /// Environment
    public enum Environment {
        /// Production Environment
        case Production
        /// Sandbox Environment
        case Sandbox
        /// QA environment
        case QA
    }

    /// API consumer credentials
    public struct APICredentials {
        let username: String
        let password: String

        /// Create credentials with username and password
        /// - Parameter username: the username
        /// - Parameter password: the password
        /// - Reference: [API Authentication](https://developers.finixpayments.com/#authentication)
        public init(username: String, password: String) {
            self.username = username
            self.password = password
        }

        var authorizationHeader: String {
            let authCredentials = "\(username):\(password)"
            guard let authData = authCredentials.data(using: .utf8) else {
                fatalError("could not encode authentication credentials")
            }
            let b64encodedCredentials = authData.base64EncodedString()
            return "Basic \(b64encodedCredentials)"
        }
    }
}

/// Ecapsulate the environment
enum FinixAPIEndpoint {
    case Sandbox
    case Live
    case QA

    /// endpoint URL
    var url: URL {
        switch self {
        case .Sandbox:
            return URL(string: "https://cardpresent-orchestrator-http.sb.finixops.com/")!
        case .Live:
            return URL(string: "https://cardpresent-orchestrator-http.prod.finixops.com/")!
        case .QA:
            return URL(string: "https://cardpresent-orchestrator-http.qa.finixops.com/")!
        }
    }

    /// endpoint URL
    static func endpoint(_ env: Finix.Environment) -> URL {
        switch env {
        case .Production:
            return FinixAPIEndpoint.Live.url
        case .Sandbox:
            return FinixAPIEndpoint.Sandbox.url
        case .QA:
            return FinixAPIEndpoint.QA.url
        }
    }

    enum Gateway: String, Encodable {
        // If environment = SB -> DUMMY_V1
        // If environment = PROD -> FINIX_V1
        init(_ environment: Finix.Environment) {
            switch environment {
            case .Production:
                self = .prod
            case .Sandbox:
                self = .sandbox
            case .QA:
                self = .prod
            }
        }

        case sandbox = "DUMMY_V1"
        case prod = "FINIX_V1"
    }
}
