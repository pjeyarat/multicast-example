#include <stdio.h>
#include "msock.h"

int main(){
    printf("starting multicast listener\n");
	msock mock("224.0.0.107", "10.0.0.135", 319);
	mock.listen();
    while(1){
        int received;
        unsigned char buff[1024];
        received = mock.recv(buff, 1024);
        printf("received %d bytes", received);
    }
}
