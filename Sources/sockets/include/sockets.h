
#import <sys/socket.h>
#import <sys/un.h>
#import <unistd.h>

#import <netinet/in.h>
#import <netdb.h>
#import <arpa/inet.h>

#import <stdio.h>
#import <stdlib.h>
#import <string.h>

typedef int
BSDSocketID,
BSDConnection;

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
BSDConnection
SocketConnect(const BSDSocket* Socket);

void
SocketSend(const BSDSocket* Socket, const char* Message);
