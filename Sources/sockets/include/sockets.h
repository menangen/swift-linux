
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <string.h>

void socketStart(const char* Message, const char* socketPath);
