//
//  sockets.swift
//  linux
//
//  Created by menangen on 12.01.2019.
//
import Foundation
import sockets

class UnixSocket {
    private var sock: UnsafePointer<BSDSocket>
    private var connection: BSDConnection?
    
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

class UDPSocket {
    private var sock: UnsafePointer<UDPBSDSocket>

    init(_ port: UInt16 = 5000) {
        self.sock = UDPSocketOpen(String(port))
    }
    
    func read() -> Data {
        var udpPacket: UDPPacket = UDPSocketRead(self.sock)
        
        return Data(bytes: &udpPacket.data, count: Int(udpPacket.size))
    }
    
    func close() {
        UDPSocketClose(self.sock)
    }
}
