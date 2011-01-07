#include "mbed.h"
#include "EthernetNetIf.h"
#include "XMPPClient.h"

EthernetNetIf ethernet;    

char userName[] = "mbed";
char password[] = "mirror";
char serverDomain[] = "ceit.org";    

void callback_msg(char* msg);

IpAddr serverIpAddr(10,1,1,5);

XMPPClient xmpp(serverIpAddr, serverDomain, callback_msg);

void callback_msg(char* msg){

    printf("Message: %s\r\n\r\n", msg);
    xmpp.send_message("mirror@ceit.org", msg);

}


int main() {
  
    printf("\r\n");
    printf("############### XMPP TCP client #######\r\n");
    printf("\r\n");
    
    EthernetErr ethErr = ethernet.setup();
    if(ethErr){
        printf("Ethernet Error %d\r\n", ethErr);  
    } else {
        printf("mbed is online...\r\n");
    }
    
    if(xmpp.connect(userName, password)){
        printf("\r\nConnect to server sucessed ..\r\n");
    } else {
        printf("\r\nConnect to server failed ..\r\n");
        return -1;
    }
    
    xmpp.send_message("mirror@ceit.org", "Im in Brisbane");
    xmpp.send_message("mirror@ceit.org", "Now mbed is an echo server..");

    printf("\r\nEchoing ..\r\n");
    
    int flag = 0;
    
    while(!flag){
        Net::poll();
        wait(1);
    }
    
    xmpp.close();
    
    printf("#### End of the test.. ####\r\n\r\n");
}