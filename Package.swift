// swift-tools-version:4.2
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "linux-udp-server",
    dependencies: [
        // Dependencies declare other packages that this package depends on.
        // .package(url: /* package url */, from: "1.0.0"),
    ],
    targets: [
        .testTarget(
            name: "cpuTests",
            dependencies: ["perlin"]),
        .target(
            name: "perlin",
            dependencies: [],
            path: "Sources/perlin"),
        .target(
            name: "sockets",
            dependencies: [],
            path: "Sources/sockets"),
        .target(
            name: "linux",
            dependencies: ["perlin", "sockets"])
    ]
)
