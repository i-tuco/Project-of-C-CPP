#define _GNU_SOURCE
#include "sysutil.h"
#include "buffer.h"
#include <sys/epoll.h>

int main(int argc, char const *argv[])
{
    //创建client套接字
    int sockfd = tcp_client(0);
    //调用非阻塞connect函数
    int ret = nonblocking_connect(sockfd, "localhost", 9981, 5000);
    if(ret == -1)
    {
        perror("Connect Timeout .");
        exit(EXIT_FAILURE);
    }

    //将三个fd设置为Non-Blocking
    activate_nonblock(sockfd);
    activate_nonblock(STDIN_FILENO);
    activate_nonblock(STDOUT_FILENO);


    buffer_t recvbuf; //sockfd -> Buffer -> stdout
    buffer_t sendbuf; //stdin -> Buffer -> sockfd

    //初始化缓冲区
    buffer_init(&recvbuf);
    buffer_init(&sendbuf);


    //创建epoll
    int epollfd = epoll_create1(0);
    if(epollfd == -1)
        ERR_EXIT("create epoll");
    struct epoll_event events[1024];

    uint32_t sockfd_event = 0;
    uint32_t stdin_event = 0;
    uint32_t stdout_event = 0;

    epoll_add_fd(epollfd, sockfd, sockfd_event);
    epoll_add_fd(epollfd, STDIN_FILENO, stdin_event);
    epoll_add_fd(epollfd, STDOUT_FILENO, stdout_event);


    while(1)
    {
        //重新装填epoll事件
        sockfd_event = 0;
        stdin_event = 0;
        stdout_event = 0;
        //epoll无法每次都重新装填，所以给每个fd添加一个空事件
        
        if(buffer_is_readable(&sendbuf))
        {
            sockfd_event |= kWriteEvent;
        }
        if(buffer_is_writeable(&sendbuf))
        {
            stdin_event |= kReadEvent;
        }
        if(buffer_is_readable(&recvbuf))
        {
            stdout_event |= kWriteEvent;
        }
        if(buffer_is_writeable(&recvbuf))
        {
            sockfd_event |= kReadEvent;
        }

        epoll_mod_fd(epollfd, sockfd, sockfd_event);
        epoll_mod_fd(epollfd, STDIN_FILENO, stdin_event);
        epoll_mod_fd(epollfd, STDOUT_FILENO, stdout_event);


        //监听fd数组
        int nready = epoll_wait(epollfd, events, 1024, 5000);
        if(nready == -1)
            ERR_EXIT("epoll wait");
        else if(nready == 0)
        {
            printf("epoll timeout.\n");
            continue;
        }
        else
        {
            int i;
            for(i = 0; i < nready; ++i)
            {
                int peerfd = events[i].data.fd;
                int revents = events[i].events;
                if(peerfd == sockfd && revents & kReadREvent)
                {
                    //从sockfd接收数据到recvbuf
                    if(buffer_read(&recvbuf, peerfd) == 0)
                    {
                        fprintf(stderr, "server close.\n");
                        exit(EXIT_SUCCESS);
                    } 
                }
                    
                if(peerfd == sockfd && revents & kWriteREvent)
                {
                    buffer_write(&sendbuf, peerfd); //将sendbuf中的数据写入sockfd
                }

                if(peerfd == STDIN_FILENO && revents & kReadREvent)
                {
                    //从stdin接收数据写入sendbuf
                    if(buffer_read(&sendbuf, peerfd) == 0)
                    {
                        fprintf(stderr, "exit.\n");
                        exit(EXIT_SUCCESS);
                    } 
                }

                if(peerfd == STDOUT_FILENO && revents & kWriteREvent)
                {
                    buffer_write(&recvbuf, peerfd); //将recvbuf中的数据输出至stdout
                }
            }
        }

    }

}