#include "msock.h"

msock::msock(string g, string i, int p){
	group = g;
	port = p;
    interface = i;
}

bool msock::listen(){
	fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(fd<0){
		perror("socket");
        return false;
	}
	unsigned int multi_listen = 1;
	if( setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char *)&multi_listen, sizeof(multi_listen)) < 0){
		perror("address reuse failed!");
        return false;
	}
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY); // differs from sender
    addr.sin_port = htons(port);
    if (bind(fd, (struct sockaddr*) &addr, sizeof(addr)) < 0) {
        perror("bind");
        return false;
    }

    struct ip_mreq mreq;
    mreq.imr_multiaddr.s_addr = inet_addr(group.c_str());
    mreq.imr_interface.s_addr = inet_addr(interface.c_str());
    if (setsockopt(
            fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*) &mreq, sizeof(mreq)) < 0){
        perror("setsockopt");
        return false;
    }
}

int msock::recv(unsigned char *buff, int len){
    unsigned int addrlen = sizeof(addr);
    int received = recvfrom(fd, buff, len, 0, (struct sockaddr *) &addr, &addrlen);
    return received;
}

int msock::send(unsigned char *buff, int len){
    int sent = sendto(fd, buff, len, 0, (struct sockaddr*) &addr, sizeof(addr));
    return sent;
}

bool msock::connect(){
    struct in_addr out_addr;
	fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(fd<0){
		perror("socket");
        return false;
	}  
    out_addr.s_addr = inet_addr(interface.c_str());   // your outgoing interface IP
    if (setsockopt(fd, IPPROTO_IP, IP_MULTICAST_IF, (char *)&out_addr,sizeof(out_addr))== -1) {
        perror("Error setting outgoing interface");
        exit(1);
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(group.c_str());
    addr.sin_port = htons(port);  
}

msock::~msock(){

}
