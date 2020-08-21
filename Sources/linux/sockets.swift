//
//  sockets.swift
//  linux
//
//  Created by menangen on 12.01.2019.
//
import Foundation
import sockets

enum SocketError: Error {
    case open
}

class UnixSocket {
    private var sock: UnsafePointer<BSDSocket>
    
    init(_ path: String = "/tmp/gameserver") {
        self.sock = UnixSocketOpen(path)
    }
    
    deinit {
        self.close()
    }
    
    func connect() throws {
        guard SocketConnect(self.sock) else {
            throw SocketError.open
        }
    }
    
    func close() {
        SocketClose(self.sock)
    }
    
    func read() -> Data {
        var buffer: StreamSocketBuffer = SocketRead(self.sock)
        
        return Data(bytes: &buffer.data, count: Int(buffer.size))
    }
    
    func send(_ data: Data) {
        
        let res: Bool =
        data.withUnsafeBytes {
            SocketSend(self.sock, $0, data.count)
        }
        
        print(res)
    }
}

class UDPSocket {
    private var sock: UnsafePointer<UDPBSDSocket>

    init(_ port: UInt16 = 5000) {
        self.sock = UDPSocketOpen(String(port))
    }
    
    deinit {
        self.close()
    }
    
    func read() -> Data {
        var udpPacket: UDPPacket = UDPSocketRead(self.sock)
        
        return Data(bytes: &udpPacket.data, count: Int(udpPacket.size))
    }
    
    func close() {
        UDPSocketClose(self.sock)
    }
}
