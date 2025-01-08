//
//  DeviceManager.swift
//  Demo
//
//  Created by Jack Tihon on 3/19/24.
//

import Foundation
import PaxEasyLinkControllerWrapper

public typealias DeviceId = String

public struct DeviceInfo {
    public let deviceId: DeviceId
    public let name: String?
}

extension DeviceInfo {
    init(_ info: BluetoothInfo) {
        deviceId = info.deviceId
        name = info.deviceName
    }

    init(_ deviceId: DeviceId, name: String = "") {
        self.deviceId = deviceId
        self.name = name
    }
}

// TODO: add logger
// NOTE: callbacks delivered on the main queue
class DeviceManager: NSObject {
    override public init() {
        easyLinkController = PaxEasyLinkControllerWrapper.getInstance()
        super.init()
    }

    private let easyLinkController: PaxEasyLinkController

    static let SearchTimeoutMS: Int = 30 * 1000 // (30 seconds)
    weak var delegate: DeviceManagerDelegate?

    private let workQueue = DispatchQueue(label: "com.finix.DeviceManager", qos: .background)

    func isConnected() -> Bool {
        easyLinkController.isConnected()
    }

    // memoize devices by id
    private var seenDevices: [DeviceId: DeviceInfo] = [:]

    func startScan() {
        seenDevices = [:]
        workQueue.async {
            // Is this really milliseconds???
            self.easyLinkController.startSearchDev(Self.SearchTimeoutMS) { info in
                debugPrint("found device")
                guard let info = info else {
                    debugPrint("no info!")
                    return
                }
                debugPrint("deviceId: \(info.deviceId ?? "unknown")")
                debugPrint("deviceName: \(info.deviceName ?? "unknown")")
                guard let deviceId = info.deviceId else {
                    debugPrint("no deviceid")
                    return
                }
                debugPrint("deviceId = \(deviceId)")
                let deviceInfo = DeviceInfo(info)
                if self.seenDevices[deviceInfo.deviceId] == nil {
                    self.seenDevices[deviceId] = deviceInfo
                    DispatchQueue.main.async {
                        self.delegate?.didDiscoverDevice(deviceInfo)
                    }
                }
            }
        }
    }

    func connectDevice(_ deviceId: DeviceId) {
        workQueue.async { [self] in
            let ret = easyLinkController.connectDevice(deviceId) { addr, name in
                debugPrint("addr: \(addr ?? "none") name: \(name ?? "none") has been disconnected.")
            }

            DispatchQueue.main.async { [self] in
                switch ret {
                case EL_RET_OK, EL_COMM_RET_CONNECTED:
                    if easyLinkController.isConnected() {
                        debugPrint("connected")
                        let info = seenDevices[deviceId] ?? .init(deviceId)
                        delegate?.didConnect(info)
                    } else {
                        debugPrint("not connected")
                        delegate?.connectionError(deviceId)
                    }
                case EL_SDK_RET_COMM_CONNECT_ERR:
                    debugPrint("connect error")
                    delegate?.connectionError(deviceId)
                default:
                    debugPrint("error")
                    delegate?.connectionError(deviceId)
                }
            }
        }
    }

    func disconnect() -> Bool {
        let rv = easyLinkController.closeDevice()

        guard rv == EL_RET_OK else {
            return false
        }

        delegate?.didDisconnect()
        return true
    }
}

protocol DeviceManagerDelegate: AnyObject {
    func didDiscoverDevice(_ info: DeviceInfo)
    func didConnect(_ info: DeviceInfo)
    func connectionError(_ deviceId: String)
    func didDisconnect()
}
