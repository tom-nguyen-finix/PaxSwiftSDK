// swift-tools-version:5.5
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "PaxSwiftSDK",
    platforms: [
        .iOS("17.6")
    ],
    products: [
        .library(
            name: "PaxSwiftSDK",
            targets: ["PaxSwift"]
        ),
    ],
    targets: [
        .binaryTarget(
            name: "PaxSwift",
            path: "./Sources/PaxSwift.xcframework"
        )
    ]
)
