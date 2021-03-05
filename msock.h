#ifndef __MSOCK_H__
#define __MSOCK_H__

#include <string>

extern "C" {
#include <stdio.h>          /* printf(), snprintf() */
#include <stdlib.h>         /* strtol(), exit() */
#include <sys/types.h>
#include <sys/socket.h>     /* socket(), setsockopt(), bind(), recvfrom(), sendto() */
#include <errno.h>          /* perror() */
#include <netinet/in.h>     /* IPPROTO_IP, sockaddr_in, htons(), htonl() */
#include <arpa/inet.h>      /* inet_addr() */
#include <unistd.h>         /* fork(), sleep() */
#include <sys/utsname.h>    /* uname() */
#include <string.h>         /* memset() */
}

using namespace std;

//udp
//able to listen on a port and interface
// able to send and receive on a port and interface

class msock{
	public:
		msock(string group, string interface, int port);
		~msock();
		bool listen();
		bool connect();
        int recv(unsigned char *buff, int len);
        int send(unsigned char *buff, int len);

	private:
		int fd;
		string group;
        string interface;
		int port;
        struct sockaddr_in addr;
};

#endif
