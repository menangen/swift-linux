
#import <sys/socket.h>
#import <sys/un.h>
#import <unistd.h>

#import <netinet/in.h>
#import <netdb.h>
#import <arpa/inet.h>

#import <stdio.h>
#import <stdlib.h>
#import <string.h>
#import <stdbool.h>

#import "udp.h"

struct BSDSocket {
    struct sockaddr_un config;
    int id;
};
typedef struct BSDSocket BSDSocket;

const
BSDSocket*
UnixSocketOpen(const char* socketPath);

void
SocketClose(const BSDSocket* Socket);

const
bool
SocketConnect(const BSDSocket* Socket);

void
SocketSend(const BSDSocket* Socket, const uint8_t* Data, const size_t Length);
