#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#define BUFLEN 512
#define NPACK 10
#define PORT 9930
void diep(char *s)
{
perror(s);
exit(1);
}
int main(void)
{
    struct sockaddr_in si_me, si_other;
    int sockfd, i, result;
    int slen=sizeof(si_other);
    char buf[BUFLEN];
    // Crear el socket
    sockfd=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sockfd==-1)
        diep("socket");
    memset((char *) &si_me, 0, sizeof(si_me));
    // Nombrar el socket
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(PORT);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);
    result=bind(sockfd, (struct sockaddr *) &si_me, sizeof(si_me));
    if (result==-1)
        diep("bind");
    for (i=0; i<NPACK; i++)
    {
        // Recibir paquete
        result=recvfrom(sockfd, buf, BUFLEN, 0, (void *) &si_other,
        &slen);
        if (result==-1)
        diep("recvfrom()");
        printf("Received packet from %s:%d\nData:
        %s\n\n",inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port), buf);
     }
    close(sockfd);
    return 0;
}
    