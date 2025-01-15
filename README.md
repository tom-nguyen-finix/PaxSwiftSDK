# PaxSwiftSDK

## Overview
This guide helps iOS developers integrate **FINIX PaxSwiftSDK** into their applications for communicating with mPOS devices.

## Table of Contents
- [Installation](#installation)
- [Pre-requisites](#pre-requisites)
- [Integration Guide](#integration-guide)
- [Sample App](#sample-app)

## Installation
Add the SDK to your project via Swift Package Manager using:
```
https://github.com/tom-nguyen-finix/PaxSwiftSDK
```

## Pre-requisites
- iOS 17.6 or later
- Real iOS device (ARM64 simulator support coming soon)
- Add Bluetooth permission in Info.plist using key `Privacy - Bluetooth Always Usage Description`

## Integration Guide
### 1. Initialize the SDK
```swift
import PaxSwift

let finixClient = FinixClient(config: FinixConfig(
            environment: TEST_ENVIRONMENT,
            credentials: Finix.APICredentials(username: TEST_USERNAME, password: TEST_PASSWORD),
            application: TEST_APPLICATION,
            version: TEST_VERSION,
            merchantId: TEST_MERCHANT_ID,
            mid: TEST_MERCHANT_MID,
            deviceType: .Pax,
            deviceId: "")
)
finixClient.delegate = self
finixClient.interactionDelegate = self
```

### 2. Scan for devices
```swift
finixClient.startScan()

extension ViewController: FinixDelegate {
    func didDiscoverDevice(_ deviceInfo: DeviceInfo) {
        devices.append(deviceInfo)
    }
}
```

### 3. Connect to device
The device will display:
- Orange light: Ready for pairing
- Green light: Battery full
- After connection: Only green light remains
```swift
finixClient.connectDevice(device.id)

extension ViewController: FinixDelegate {
    func deviceDidConnect(_ deviceInfo: DeviceInfo) {
        connectedDevice = deviceInfo
    }
}
```

### 4. Start a Transaction
First, update the client with the device ID:
```swift
finixClient.update(deviceId: TEST_DEVICE_ID)
```
Then initiate the transaction:
```swift
let transactionAmount = Currency(amount: Int(amountDouble * 100), code: .USD)
finixClient.startTransaction(amount: transactionAmount, type: transactionType) { transferResponse, error in
    Task { @MainActor in
        // Handle using transferResponse and error
    }
}
```
Device status:
- Blue light: Waiting for card interaction
- Light turns off + beeping: Card detected

## Sample App
1. Clone the repository:
```bash
git clone https://github.com/tom-nguyen-finix/PaxSwiftSDK
```
2. Open the demo project:
```
PaxSwiftSDK/Example/PaxSwiftSDKDemo/PaxSwiftSDKDemo.xcodeproj
```
3. Run on a physical device:
    1. Tap `Scan for Devices` to show the device list view and start scanning.
     When running for the first time after installing, the bluetooth permission prompt will be shown.
     Tap `Allow` and dismiss the device list view, then tap `Scan for Devices` again.
     **This behavior can be improved by prompting the bluetooth permission before tapping `Scan for Devices`
     for the first time.**
    2. Select the device you want to pair with.
    3. After the device is connected, adjust the amount in the text field, and try Sale, Auth, or Refund buttons
       to initiate a transaction.
    4. Interact with the mPOS device with a card to finish the transaction.
