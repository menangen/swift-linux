import XCTest

import cpuTests

var tests = [XCTestCaseEntry]()
tests += cpuTests.__allTests()

XCTMain(tests)
