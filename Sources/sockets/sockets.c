//
//  Created by menangen on 11.01.19.
//  Copyright (c) 2019 menangen. All rights reserved.
//
#import "sockets.h"

void socketStart(const char* Message, const char* socketPath)
{
    // setup socket
    
    struct sockaddr_un
    socketConfig = {
        .sun_family = AF_UNIX,
        .sun_path = "/tmp/gameserver"
    };
    
    int
    unixSocket = socket(AF_UNIX, SOCK_STREAM, 0);
    printf("connfd: %d\n", unixSocket);
    
    // connect to server
    
    int
    Connection = -1;
    
    while (Connection != 0) {
        Connection = connect(unixSocket, (struct sockaddr *)&socketConfig, sizeof(socketConfig));
        printf("connect: %d\n", Connection);
        
        sleep(2);
    }
    
    // send message
    
    send(unixSocket, Message, strlen(Message), 0);
    
    /* receive messages
    char socketBuffer[4096];
    
    int len = recv(SocketConnection, socketBuffer, sizeof(socketBuffer), 0);
    if(len != 0) {
        printf("recieved response: %s\n", socketBuffer);
    }*/
    
    close(unixSocket);
}
