//
//  udp.c
//  sockets
//
//  Created by menangen on 18/01/2019.
//
#import "sockets.h"

const
UDPBSDSocket*
UDPSocketOpen(const char* port) {
    UDPBSDSocket*
    Socket = malloc( sizeof(UDPBSDSocket) );
    
    // setup socket
    Socket -> config.ai_family = AF_INET; // PF_INET
    Socket -> config.ai_socktype = SOCK_DGRAM;
    Socket -> config.ai_protocol = IPPROTO_UDP;
    Socket -> config.ai_flags = AI_PASSIVE;
    
    struct addrinfo*
    endpoint;
    
    int status =
    getaddrinfo(NULL, port, &Socket -> config, &endpoint);
    
    if (status != 0) {
        fprintf(stderr, "getaddrinfo error: %sn", gai_strerror(status));
    };
    
    Socket -> id =
    socket(endpoint -> ai_family, endpoint -> ai_socktype, endpoint -> ai_protocol);
    
    if (
        bind(Socket -> id, endpoint -> ai_addr, endpoint -> ai_addrlen)
        == -1
    ) {
        printf("Error bind UDP socket [id: %d]\n", Socket -> id);
    }
    
    freeaddrinfo(endpoint);
    return Socket;
}

const
UDPPacket
UDPSocketRead(const UDPBSDSocket* Socket)
{
    static
    UDPPacket
    SocketBuffer;
    
    struct sockaddr_in
    receiveSockaddr;
    
    socklen_t
    receiveSockaddrLen = sizeof(receiveSockaddr);
    
    printf("Reading UDP data \n");
    ssize_t
    bytes = recvfrom(Socket -> id, SocketBuffer.data, 256, 0, (struct sockaddr *)&receiveSockaddr, &receiveSockaddrLen);
    
    if ( bytes != 0 ) {
        printf("Recieved response (%lu bytes): %s\n", bytes, SocketBuffer.data);
        SocketBuffer.size = bytes;
    }
    
    return SocketBuffer;
}

void
UDPSocketClose(const UDPBSDSocket* Socket)
{
    printf("Closing socket \n\n");
    close(Socket -> id);
}
