//
//  Created by menangen on 11.01.19.
//  Copyright (c) 2019 menangen. All rights reserved.
//
#import "sockets.h"

void unixSocketStart(const char* Message, const char* socketPath)
{
    // setup socket
    
    struct sockaddr_un
    socketConfig = {
        .sun_family = AF_UNIX,
        .sun_path = "/tmp/gameserver"
    };
    
    if (strncmp("", socketPath, 64)) strncpy(socketConfig.sun_path, socketPath, 64);
    
    int
    unixSocket = socket(AF_UNIX, SOCK_STREAM, 0);
    printf("Opening unix socket %s [%d]\n", socketConfig.sun_path, unixSocket);
    
    // connect to server
    
    int8_t
    Connection = -1;
    
    while (Connection != 0) {
        Connection = connect(unixSocket, (struct sockaddr *)&socketConfig, sizeof(socketConfig));
        
        switch (Connection) {
            case 0:
                printf("Connected to %s\n", socketPath);
                
                // send message
                
                send(unixSocket, Message, strlen(Message), 0);
                
                // receive messages
                /*
                char
                socketBuffer[4096];

                int
                len = recv(Connection, socketBuffer, sizeof(socketBuffer), 0);
                
                if ( len != 0 ) {
                    printf("Recieved response: %s\n", socketBuffer);
                }
                */
                
                break;
                
            default:
                printf("Error connect to %s socket\n", socketPath);
                break;
        }
        
        
        sleep(2);
    }
    
    close(unixSocket);
}
