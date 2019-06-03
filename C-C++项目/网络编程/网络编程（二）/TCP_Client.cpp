//分割IO实现分割数据的收发过程
//父进程负责接收，子进程负责发送
//./c.out 127.0.0.1 8000
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30

void error_handling(const char *message);
void read_routine(int sock, char *buf);
void write_routine(int sock, char *buf);

int main(int argc, char * argv[])
{
    int sock;
    pid_t pid;
    struct sockaddr_in serv_addr;
    int str_len;
    char buf[BUF_SIZE];

    if(argc != 3)
    {
        exit(1);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock == -1)
        error_handling("socket error");
    
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;//IPv4协议簇
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));//端口号

    if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
        error_handling("connect error");
    else
        puts("connected...");
    
    pid = fork();
    if(pid == 0)//子进程写
        write_routine(sock, buf);
    else//父进程读
        read_routine(sock, buf);
    
    close(sock);

    return 0;
}

void error_handling(const char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

//这里实现读入有关代码
void read_routine(int sock, char *buf)
{
    while(1)
    {
        int str_len = read(sock, buf, BUF_SIZE);
        if(str_len == 0)
            return;//接受到EOF结束符时返回
        
        buf[str_len] = 0;
        printf("message from server: %s\n", buf);
    }
}

//这里负责实现输出有关代码
void write_routine(int sock, char *buf)
{
    while(1)
    {
        fgets(buf, BUF_SIZE, stdin);
        if(!strcmp(buf, "q\n") || !strcmp(buf, "Q\n"))
        {
            shutdown(sock, SHUT_WR);
            return;
        }
        write(sock, buf, strlen(buf));
    }
}
