// swift-tools-version:5.0
import PackageDescription

let package = Package(
    name: "linux",
    dependencies: [],
    targets: [
        .target(
            name: "quickjs",
            dependencies: [],
            path: "Sources/quickjs"),
        .target(
            name: "linux",
            dependencies: ["quickjs"])
    ]
)
