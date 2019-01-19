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

let s = Socket()
s.connect()
s.send("Hello from swift".data(using: .utf8)!)
s.close()

print("Completed")
