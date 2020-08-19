//
//  main.swift
//  testingSwift
//
//  Created by menangen on 21.08.14.
//  Copyright (c) 2014 menangen. All rights reserved.
//

import perlin
import sockets
import Foundation

let s = UnixSocket()
let q = OperationQueue()

do {
    try s.connect()
    let block = BlockOperation {
        print(s.read())
    }

    q.addOperations([block], waitUntilFinished: false)
    sleep(4)
    s.send("Hello from swift".data(using: .utf8)!)
    
    print("Completed")
}
catch {
    print("Error Unix socket opening")
}
