//
//  sockets.swift
//  linux
//
//  Created by menangen on 12.01.2019.
//
import Foundation
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
    
    func send(_ data: Data) {
        
        data.withUnsafeBytes { (u8Ptr: UnsafePointer<UInt8>) in // UnsafeRawPointer(u8Ptr)
            SocketSend(self.sock, u8Ptr, data.count)
        }
    }
}
