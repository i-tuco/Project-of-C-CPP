//基于IO复用echo服务端（select()函数使用）
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/select.h>

#define BUF_SIZE 100
void error_handling(char *message);

int main(int argc, const char * argv[]) {
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_adr, clnt_adr;
    struct timeval timeout;
    fd_set reads, cpy_reads;

    socklen_t adr_sz;
    int fd_max, str_len, fd_num;
    char buf[BUF_SIZE];
    if (argc != 2) {
        printf("Usage: %s <port> \n", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));

    if(bind(serv_sock, (struct sockaddr *) &serv_adr, sizeof(serv_adr)) == -1)
        error_handling("bind() error");
    if(listen(serv_sock, 5) == -1)
        error_handling("listen() error");

    FD_ZERO(&reads);
    //向要传到select函数第二个参数的fd_set变量reads注册服务器端套接字
    FD_SET(serv_sock, &reads);
    fd_max = serv_sock;

    while (1)
    {
        cpy_reads = reads;
        timeout.tv_sec = 5;
        timeout.tv_usec = 5000;

        //监听服务端套接字和与客服端连接的服务端套接字的read事件
        if ((fd_num = select(fd_max + 1, &cpy_reads, 0, 0, &timeout)) == -1)
            break;
        if(fd_num == 0)
            continue;

        if (FD_ISSET(serv_sock, &cpy_reads))//受理客服端连接请求
        {
            adr_sz = sizeof(clnt_adr);
            clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_adr, &adr_sz);
            FD_SET(clnt_sock, &reads);
            if(fd_max < clnt_sock)
                fd_max = clnt_sock;
            printf("connected client: %d \n", clnt_sock);
        }
        else//转发客服端数据
        {
            str_len = read(clnt_sock, buf, BUF_SIZE);
            if (str_len == 0)//客服端发送的退出EOF
            {
                FD_CLR(clnt_sock, &reads);
                close(clnt_sock);
                printf("closed client: %d \n", clnt_sock);
            }
            else
            {
                //接收数据为字符串时执行回声服务
                write(clnt_sock, buf, str_len);
            }
        }
    }

    close(serv_sock);
    return 0;
}


void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}