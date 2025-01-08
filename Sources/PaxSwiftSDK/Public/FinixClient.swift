//
//  FinixClient.swift
//  FinixPOS
//
//  Created by Jack Tihon on 2/29/20.
//  Copyright © 2020 Finix Payments, Inc. All rights reserved.
//

import Foundation

/// The interface to the SDK
public class FinixClient {
    /// interested parties can register as delegates
    public weak var delegate: FinixDelegate?

    /// This delegate provides card reader information and status prompts. e.g. when to insert/tap/swipe
    public weak var interactionDelegate: FinixClientDeviceInteractionDelegate?

    private(set) var logger: FinixLogger = {
        let logger = FinixLogger()
        logger.component = .all
        logger.logger.level = .verbose
        return logger
    }()

    let endpoint: URL
    let session: URLSession // The session to make requests on. Setting `config` will create a session

    // Card Reader
    let paxManager: PaxManager
    let deviceManager: DeviceManager
    var config: FinixConfig

    var connectedDevice: DeviceInfo?

    public init(config: FinixConfig) {
        self.config = config
        endpoint = FinixAPIEndpoint.endpoint(config.environment)

        let sessionConfiguration = URLSessionConfiguration.default
        sessionConfiguration.httpAdditionalHeaders = [
            "Authorization": config.credentials.authorizationHeader,
            // SDK version
            // app version
        ] // TODO: add app and version headers here

        session = URLSession(configuration: sessionConfiguration)

        deviceManager = DeviceManager()
        paxManager = PaxManager(logger: logger)
        paxManager.delegate = self
        deviceManager.delegate = self

        let VersionKey = "CFBundleVersion"
        let ShortVersionKey = "CFBundleShortVersionString"
        let shortVersion = (Bundle.main.object(forInfoDictionaryKey: ShortVersionKey) as? String) ?? ""
        let bundleVersion = (Bundle.main.object(forInfoDictionaryKey: VersionKey) as? String) ?? ""
        logger.info("syncSDK for \(shortVersion)(\(bundleVersion))")
    }

    /// Returns true if a there is a card reader connected
    public func isReaderConnected() -> Bool {
        deviceManager.isConnected()
    }

    /// Initialize the SDK. Call this before using the API. It will call `completion` when it's done.
    /// - Parameter config: The merchant's configuration
    /// - Parameter completion: The handler will be invoked on completion of initialization
    /// - Attention: Do not attempt to use the API until this call completes.

    public func stopCurrentOperation() {
        paxManager.cancelTransaction()
    }
    
    /// - `Update Device ID` it will update the device id after connecting to the device.
    public func update(deviceId:String){
        config.deviceId = deviceId
    }
    
}
