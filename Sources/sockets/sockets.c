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
    
#ifdef __APPLE__
    uint8_t
    noPipeError = 1;
    setsockopt(UnixSocket -> id, SOL_SOCKET, SO_NOSIGPIPE, (void *)&noPipeError, sizeof(int));
#endif
    
    if (strncmp("", socketPath, 64)) strncpy(UnixSocket -> config.sun_path, socketPath, 64);
    
    printf("Init Unix socket [ %s id: %d]\n", UnixSocket -> config.sun_path, UnixSocket -> id);
    
    return UnixSocket;
}

void
SocketClose(const BSDSocket* Socket)
{
    printf("Closing socket \n\n");
    close(Socket -> id);
}

const
bool
SocketConnect(const BSDSocket* Socket) {
    // printf("Opening unix socket wih id: [%d]\n", Socket -> id);
    
    return
    0 == connect(
                 Socket -> id,
         (struct sockaddr *)
                 &Socket -> config,
         sizeof(
                 Socket -> config
         ));
}

const
bool
SocketSend(const BSDSocket* Socket, const uint8_t* Data, const size_t Length)
{
    printf("Sending Unix socket Data \n");

    if (
        -1 ==
        send(
             Socket -> id,
             Data,
             Length,
#ifdef __APPLE__
             0
#else
             MSG_NOSIGNAL
#endif
             )
    ) {
        printf("Sending ERROR \n");
        return false;
    };
    return true;
}

const
StreamSocketBuffer
SocketRead(const BSDSocket* Socket)
{
    printf("Reading Data \n");
    
    static
    StreamSocketBuffer
    buffer;
    
    buffer.size = recv(Socket -> id, buffer.data, sizeof(buffer.data), 0);
    
    if ( buffer.size > 0 ) {
        printf("Recieved response: %s\n", buffer.data);
    }
    else {
        printf("Socket closed");
    }
    
    return buffer;
}
