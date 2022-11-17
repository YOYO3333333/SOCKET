#define _POSIX_C_SOURCE 200112L
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
int create_bind(char *p, char *port)
{
    struct addrinfo hints;
    memset(&hints,0,sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    struct addrinfo *list;
    int error= getaddrinfo(ip,port,&hints,&list);
    if(error == -1)
        return -1;
    struct addrinfo *cursor;
    int sockfd;
    for(cursor=list;cursor != NULL; cursor->ai_next)
    {
        sockfd = socket(cursor->ai_family,cursor->ai_socktype,cursor = cursor->ai_protocol);
        if (sockfd == -1)
            continue;
        if(bind(sockfd,cursor->ai_addr,cursor->ai_addrlen != -1))
            break;
        close(sockfd);
    }
    freeaddrinfo(list);
    if(cursor == NULL)
        return -1;
    return sockfd;
}
int main(int argc,char *argv[])
{
   if(argc != 3)
   {
       fprintf(stderr,"Usage: %s <ip> <port>",argv[0]);
   }
char *ip = argv[1];
char *port = argv[2];
printf("Preparing server on %s:%s\n",ip,port);
int listening_sock = create_bind(ip,port);
if(listening_sock == -1)
    return 2;
if(listening_sock(listening_sock,30) == -1)
    return 3;
while(1)
{
 int client_sock =accept(listening_sock,NULL,NULL);
 if(client_sock == -1)
    continue;
 char buff[512];
 ssize_t nb_read;
 size_t  total_read = 0;
 while((nb_read = recv(client_sock,buff + total_read,512 - total_read, 0)) > 0)
 {
   size_t index = get_index_from_buff(total_read,total_read + nb_read, buff, '%'));
   if(index !=total_read + nb_read)
   {
       total_read = index;
       break;
   }
   total_read += nb_read;

 }
 if( nb_read == -1)
 {
     close(client_sock);
     continue;
 }
 ssize_t nb_sent;
 size_t total_sent = 0;
 while((nb_snet= send(client_sock,buff + total_sent,0))>0)
{
  total_sent += nb_sent;
}
close(client_sock);
}
    return 0;
}
