//
//  main.swift
//  swift-linux
//
//  Created by menangen on 17.08.[14..19].
//  Copyright (c) 2014 menangen. All rights reserved.
//

import quickjs

let JSSourceCode = """
World.move(32)
"""

class World {
    func move(_ to: UInt8) {
        print("Moving to \(to)")
    }
}

let world = World()

class JSState {
    
    init() {
        let Runtime = JS_NewRuntime()
        let Context = JS_NewContextRaw(Runtime)

        JS_AddIntrinsicBaseObjects(Context)
        JS_AddIntrinsicEval(Context)

        let GlobalObject = JS_GetGlobalObject(Context)
        let WorldObject = JS_NewObject(Context)

        let swiftCallback : @convention(c) (OpaquePointer?, JSValue, Int32, UnsafeMutablePointer<JSValue>?) -> JSValue = {
            (Context, Value, argc, argv) in
            
            if let arguments = argv {/*
                for index in 0..<argc {
                    
                    let argument = arguments[Int(index)]
                    let str = String(cString: JS_ToCString(Context, argument))
                    
                    print(str)
                }*/
                
                var val: Int32 = 0
                
                JS_ToInt32(Context, &val, arguments[0])
                
                world.move(UInt8(val))
                
            }
            
            return JS_NewInt32(Context, 777)
        }
        
        JS_SetPropertyStr(Context,
                          WorldObject,
                          "move",
                          JS_NewCFunction(Context, swiftCallback, "move", 1))

        JS_SetPropertyStr(Context, GlobalObject, "World", WorldObject)

        JS_FreeValue(Context, GlobalObject)



        let returnType = JS_Eval(Context,
                              JSSourceCode,
                              JSSourceCode.count,
                              "<evalScript>",
                              JS_EVAL_TYPE_GLOBAL)

        JS_FreeContext(Context)
        JS_FreeRuntime(Runtime)

        print("End", returnType.u.int32)
    }
}

JSState()
