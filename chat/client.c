/*************************************************************************
> File Name: server.c
> Author:FENGKAI 
> Mail: 763608087@qq.com
> Created Time: 2017年03月20日 星期一 03时34分55秒
************************************************************************/


#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<pthread.h>
#include<string.h>
#include<poll.h>
#include<stdio.h>

#define SERVERIP 0
#define SERVERPORT 8080

#define BUFSIZE 1024
#define USER_LIMIT 6
#define FD_LIMIT 65536

typedef struct Uclient_data
{
    struct sockaddr_in address;
    char *write_buf;
    char buf[BUFSIZE];//读缓存
}client_data;

int Start()
{
    int sock =0;
    sock =socket(AF_INET,SOCK_STREAM,0);
    if(sock<0)
    {
        perror("sock");
        return 1;
    }
    struct sockaddr_in server;
    const char *ip =itoa((int)SERVERIP);
    server.sin_addr.s_addr =inet_addr(ip);
    server.sin_family =AF_INET;
    server.sin_port= htons(SERVERPORT);
    if(bind(sock,(struct sockaddr*)&server,sizeof(server))<0)
    {
        perror("bind");
        return 2;
    }
    if(listen(sock,5)<0)
    {
        perror("bind");
        return 3;
    }
    return sock;
}

int main()
{
    int listen_sock=Start();
    client_data *user=malloc(FD_LIMIT*sizeof(client_data)); 
    struct pollfd fds[USER_LIMIT+1];
    int user_count =1;
    int i=0;
    for(i=1;i<=USER_LIMIT;i++)
    {
        fds[i].fd=-1;
        fds[i].events=0;
    }
    fds[0].fd =listen_sock;
    fds[0].events=POLLIN;
    fds[0].revents=0;
    int ret;
    while(1)
    {
        ret=poll(fds,user_count+1,-1);
        if(ret<0 )
        {
            perror("poll");
            break;
        }
        for(i=0;i<user_count;i++)
        {
            if((fds[i].fd==listen_sock)&&(fds[i].revents&POLLIN))
            {
                struct sockaddr_in client;
                socklen_t len =sizeof(client);
                int sock=0;
                sock = accPt(sock,(struct sockaddr*)&client,&len);
               if(sock<0)
                {
                    perror("accPt");
                    continue;
                }
                user_count++;
                user[sock].address =client;
                fds[user_count].fd=sock;
                fds[user_count].events=POLLIN|POLLERR|POLLRDHUP;
                fds[user_count].revents=0;
                printf("now have %d user\n",user_count);
            }
            else if(fds[i].revents ==POLLERR)
            {
                ;
            }
            else if(fds[i].revents==POLLIN)
            {
                int refd=fds[i].revents;
                memset(user[refd].buf,'\0',BUFSIZE);
                ssize_t s =recv(refd,user[refd].buf,BUFSIZE);
                if(s<0)
                {
                    close(refd);
                    user[fds[i].fd]=user[fds[user_count].fd];
                    fds[i]=fds[user_count];
                    i--;
                    user_count--;
                }
                else if(s>0)
                {
                    int j=0;
                    for(j=1;j<user_count;j++)
                    {
                        if(fds[j].fd==refd)
                        {
                            continue;
                        }
                        fds[j].events|=~POLLIN;
                        fds[j].events|=POLLOUT;
                        user[fds[j].fd].write_buf=user[refd].buf;
                    }
                }
            }
            else if(fds[i].revents&POLLOUT)
            {
                int refd= fds[i].fd;
                if(!user[refd].write_buf)
                {
                    continue;
                }
                ret =send(refd,user[refd].write_buf,strlen(user[refd].write_buf,0));
                user[refd].write_buf=NULL;
                fds[i].events|=~POLLOUT;
                fds[i].events|=POLLIN;
            }
            }
            }
            return 0;
}
