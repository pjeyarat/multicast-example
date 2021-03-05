#include <stdio.h>
#include "msock.h"

int main(){
    printf("starting multicast listener\n");
	msock mock("224.0.0.107","10.0.0.135", 319);
	mock.connect();
    while(1){
        int sent;
        unsigned char buff[5] = {0x00,0x01,0x02,0x03,0x04};
        sent = mock.send(buff, 5);
        printf("sent %d bytes", sent);
    }
}
