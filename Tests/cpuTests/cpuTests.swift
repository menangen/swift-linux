import XCTest
import perlin

let cpuFeaturesFlag: Int8 = isAVX()

final
class cpuTests: XCTestCase {

    override class func setUp() {
        let x: UInt16 = getNumCores()
        print("Number cores in system: \(x)")
    }
    
    func testAVX() throws {
        
        XCTAssertGreaterThanOrEqual(cpuFeaturesFlag, 0)
        
    }
    
    func testAVX2() throws {
        XCTAssertGreaterThanOrEqual(cpuFeaturesFlag, 1)
    }
}
