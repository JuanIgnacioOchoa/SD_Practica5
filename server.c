#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#define MAX_CLIENT 50
#define NICK_SIZE 20
#define STR_SIZE 40
#define BUFLEN 512
#define NPACK 100
#define PORT 9930

    int totalcltes = 0;
    int parametro[MAX_CLIENT];
    char user[10][NICK_SIZE];
    
    struct sockaddr_in si_me, si_other, si_clntes[MAX_CLIENT], si_clntes2[MAX_CLIENT] ;
    int sockfd;
    int slen=sizeof(si_other);
    char buf[BUFLEN];


void diep(char *s)
{
    perror(s);
    exit(1);
}
int main(void)
{
    
    int i, result;

    //printf("1\n");
    // Crear el socket
    sockfd=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    //printf("2\n");
    if (sockfd==-1)
        diep("socket");
    memset((char *) &si_me, 0, sizeof(si_me));
    //printf("3\n");
    // Nombrar el socket
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(PORT);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);
    //printf("4\n");
        result=bind(sockfd, (struct sockaddr *) &si_me, sizeof(si_me));
        if (result==-1)
            diep("bind");
        for (i=0; i<NPACK; i++)
        {
            int x = 0;
            for(x = 0; x < totalcltes; x++){
             //   printf("aaa totalcl %d -- %s\n", totalcltes, inet_ntoa(si_clntes[x].sin_addr));
            }
            // Recibir paquete
            memset(&buf[0], 0, sizeof(buf));
            x = 0;
            for(x = 0; x < totalcltes; x++){
               // printf("ccc totalcl %d -- %s\n", totalcltes, inet_ntoa(si_clntes[x].sin_addr));
            }
            printf("\n");
            result=recvfrom(sockfd, buf, BUFLEN, 0, (void *) &si_other,&slen);
            x = 0;
            for(x = 0; x < totalcltes; x++){
                //printf("ppp totalcl %d -- %s ---- %s\n", totalcltes, inet_ntoa(si_clntes[x].sin_addr),inet_ntoa(si_other.sin_addr));
            }
            printf("\n");
            if (result==-1)
            diep("recvfrom()");
            //printf("hh%d\n", buf[0]);
            printf("Received packet from %s:%d\nData:%s\n\n",inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port), buf);
            if(buf[0] == 42){
                memset(user[totalcltes], 0 , sizeof(buf));
                strcpy(user[totalcltes], buf);
                si_clntes[totalcltes] = si_other;
                si_clntes2[totalcltes] = si_other;
                int i = 0;
                for(i = 0; i <= totalcltes; i++){
                    //printf("totalcl %d -- %s\n", totalcltes, inet_ntoa(si_clntes[i].sin_addr));
                }
                totalcltes++;
            } else {
                printf("Sending... \n");
                if(sendto(sockfd, user[i], sizeof(user[i]), 0, (void *)&si_other, slen) == -1)
                diep("sendto()");
                if(sendto(sockfd, buf, BUFLEN, 0, (void *)&si_other, slen) == -1)
                    diep("sendto() 2");
                /*int i = 0;
                for(i = 0; i < totalcltes; i++){
                    //if(si_clntes[i] != si_other){
                        struct sockaddr_in si_send = si_clntes[i];
                        int x = 0;
                        //for(x = 0; x <totalcltes; x++){
                            printf("i%d-t%d  %s----%s\n",i, totalcltes, inet_ntoa(si_send.sin_addr),inet_ntoa(si_clntes[i].sin_addr));
                        /*
                        if(sendto(sockfd, user[i], sizeof(user[i]), 0, (void *)&si_send, slen) == -1)
                            diep("sendto()");
                        if(sendto(sockfd, buf, BUFLEN, 0, (void *)&si_send, slen) == -1)
                            diep("sendto() 2");
                        */
                        
                    //}
                    
                //}
            }
        }
        printf("end");
        //    parametro[totalcltes] = totalcltes;

        //    pthread_create(&tid[totalcltes], NULL, coneeccion_clte, 
        //    (void *) &parametro[totalcltes]);
    
    
    close(sockfd);
    return 0;
}

    