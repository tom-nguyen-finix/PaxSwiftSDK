// swift-tools-version:5.0
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "PaxSwiftSDK",
    platforms: [
        .iOS("13.0")
    ],
    products: [
        .library(
            name: "PaxSwiftSDK",
            targets: ["PaxSwiftSDK"]
        ),
    ],
    targets: [
        .binaryTarget(
            name: "PaxEasyLinkController",
            path: "./Sources/PaxEasyLinkController.xcframework"
        ),
        .target(
            name: "PaxEasyLinkControllerWrapper",
            dependencies: ["PaxEasyLinkController"]
        ),
        .target(
            name: "PaxSwiftSDK",
            dependencies: ["PaxEasyLinkControllerWrapper"]
        ),
        .testTarget(
            name: "PaxSwiftSDKTests",
            dependencies: ["PaxSwiftSDK"]
        ),
    ]
)
