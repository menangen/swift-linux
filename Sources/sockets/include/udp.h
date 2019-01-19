//
//  udp.c
//  sockets
//
//  Created by menangen on 19/01/2019.
//
#import "sockets.h"

struct UDPBSDSocket {
    struct addrinfo config;
    int id;
};
typedef struct UDPBSDSocket UDPBSDSocket;

struct UDPPacket {
    uint8_t data[256];
    uint8_t size;
};
typedef struct UDPPacket UDPPacket;

const
UDPBSDSocket*
UDPSocketOpen(const char* port);

const
UDPPacket
UDPSocketRead(const UDPBSDSocket* Socket);

void
UDPSocketClose(const UDPBSDSocket* Socket);
