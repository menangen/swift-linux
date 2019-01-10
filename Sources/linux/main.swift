//
//  main.swift
//  testingSwift
//
//  Created by menangen on 21.08.14.
//  Copyright (c) 2014 menangen. All rights reserved.
//

import perlin

var x: UInt16 = get_noise()

print("Number cores in system: \(x)")

isAVX();
