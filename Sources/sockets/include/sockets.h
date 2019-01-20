
#import <sys/socket.h>
#import <sys/types.h>
#import <sys/un.h>
#import <unistd.h>

#import <netinet/in.h>
#import <netdb.h>
#import <arpa/inet.h>

#import <stdio.h>
#import <stdlib.h>
#import <string.h>
#import <stdbool.h>
#import <stdint.h>

#import "udp.h"

struct BSDSocket {
    struct sockaddr_un config;
    int id;
};
typedef struct BSDSocket BSDSocket;

struct StreamSocketBuffer {
    uint8_t data[4096];
    size_t  size;
};
typedef struct StreamSocketBuffer StreamSocketBuffer;

const
BSDSocket*
UnixSocketOpen(const char* socketPath);

void
SocketClose(const BSDSocket* Socket);

const
bool
SocketConnect(const BSDSocket* Socket);

const
StreamSocketBuffer
SocketRead(const BSDSocket* Socket);

const
bool
SocketSend(const BSDSocket* Socket, const uint8_t* Data, const size_t Length);
