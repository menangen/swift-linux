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

let socket = UDPSocket(5000)
let data = socket.read()
print("Data:", String(data: data, encoding: .ascii) ?? "")
socket.close()
