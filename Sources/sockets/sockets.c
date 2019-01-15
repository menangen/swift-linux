//
//  Created by menangen on 11.01.19.
//  Copyright (c) 2019 menangen. All rights reserved.
//
#import "sockets.h"

const
BSDSocket*
UnixSocketOpen(const char* socketPath) {
    BSDSocket*
    UnixSocket = malloc( sizeof(BSDSocket) );
    
    // setup socket
    UnixSocket -> config.sun_family = AF_UNIX;
    UnixSocket -> id = socket(AF_UNIX, SOCK_STREAM, 0);
    
    if (strncmp("", socketPath, 64)) strncpy(UnixSocket -> config.sun_path, socketPath, 64);
    
    printf("Init Unix socket [ %s id: %d]\n", UnixSocket -> config.sun_path, UnixSocket -> id);
    
    return UnixSocket;
}

void
SocketClose(const BSDSocket* Socket)
{
    printf("Closing socket \n\n");
    close(Socket);
}

const
BSDConnection
SocketConnect(const BSDSocket* Socket) {
    BSDConnection
    Connection = -1;
    
    printf("Opening unix socket wih id: [%d]\n", Socket -> id);
    Connection = connect(Socket -> id, (struct sockaddr *) &Socket -> config, sizeof(Socket -> config));
    
    switch (Connection) {
        case 0:
            printf("Connected...\n");
            break;
            
        default:
            printf("Error connection to socket \n");
            break;
    }
    
    return Connection;
}


void SocketSend(const BSDSocket* Socket, const uint8_t* Data, const size_t Length)
{
    printf("Sending Data \n");
    send(Socket -> id, Data, Length, 0);
}

char SocketRead(const BSDConnection Connection)
{
    printf("Reading Data \n");
    static
    char
    socketBuffer[4096];
    
    int
    len = recv(Connection, socketBuffer, sizeof(socketBuffer), 0);
    
    if ( len != 0 ) {
        printf("Recieved response: %s\n", socketBuffer);
    }
    
    return socketBuffer;
}
