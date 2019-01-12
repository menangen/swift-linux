//
//  sockets.swift
//  linux
//
//  Created by menangen on 12.01.2019.
//

import sockets

class Socket {
    private var sock: UnsafePointer<BSDSocket>
    private var connection: BSDConnection?
    
    enum type {
        case unix
    }
    
    init(_ path: String = "/tmp/gameserver") {
        self.sock = UnixSocketOpen(path)
    }
    
    func connect() {
        self.connection = SocketConnect(self.sock)
    }
    
    func close() {
        SocketClose(self.sock)
    }
    
    func send() {
        let message = "ok"
        
        SocketSend(self.sock, message)
    }
}
