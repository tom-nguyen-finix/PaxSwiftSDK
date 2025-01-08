//
//  FinixClient+DeviceManagerDelegate.swift
//  PaxMposSDK
//
//  Created by Jack Tihon on 5/5/24.
//

import Foundation

// MARK: finding devices

public extension FinixClient {
    /// find  card readers nearby
    func startScan() {
        deviceManager.startScan()
    }

    /// connect oto a card reader by previously-found device name
    func connectDevice(_ deviceId: DeviceId) {
        deviceManager.connectDevice(deviceId)
    }

    /// disconnect SDK from device
    func disconnectDevice() -> Bool {
        deviceManager.disconnect()
    }
}

extension FinixClient: DeviceManagerDelegate {
    func didDiscoverDevice(_ info: DeviceInfo) {
        // HAX: filter out Pax D135 card reader by name. Not sure why the built-in scanner doesn't filter by device family?
//        if let name = info.name, name.prefix(5) == "D135-" {
            delegate?.didDiscoverDevice(info)
//        }
    }

    func didConnect(_ info: DeviceInfo) {
        connectedDevice = info
        delegate?.deviceDidConnect(info)
    }

    func connectionError(_ deviceId: String) {
        connectedDevice = nil
        let error = FinixError(code: .CardReaderNotConnected, message: "Connection error (deviceId: \(deviceId))")
        delegate?.deviceDidError(error)
    }

    func didDisconnect() {
        connectedDevice = nil
        delegate?.deviceDidDisconnect()
    }
}
