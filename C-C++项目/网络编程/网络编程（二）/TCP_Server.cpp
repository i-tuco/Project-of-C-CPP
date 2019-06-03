//基于多进程的并发服务器实现
//注：子进程会复制父进程拥有的所有资源
//./s.out 8000
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <signal.h>
#include <sys/wait.h>

#define BUF_SIZE 30

void error_handling(const char *message);
void read_childproc(int sig);

int main(int argc, char *argv[])
{
    //定义TCP连接变量
    int serv_sock;
    int clnt_sock;
    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size;
    int str_len;
    char buf[BUF_SIZE];
    //定义信号处理变量
    pid_t pid;
    struct sigaction act;
    int state;

    if (argc != 2)
    {
        exit(1);
    }

    //配置信号处理函数
    act.sa_handler = read_childproc;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGCHLD, &act, 0);

    //TCP套接字配置
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock == -1)
        error_handling("socket error");
    
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;//IPv4协议簇
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);//主机字节序（host)转换成网络字节序（net）(大端序)
    serv_addr.sin_port = htons(atoi(argv[1]));//端口号

    if(bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
        error_handling("bind error");
    
    if(listen(serv_sock, 5) == -1)
        error_handling("listen error");
    
    while(1)
    {
        clnt_addr_size = sizeof(clnt_addr);
        clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);
        if(clnt_sock == -1)
            continue;
        else
            puts("new client connected...");
        
        pid = fork();//创建新进程
        if(pid == -1)
        {
            close(clnt_sock);
            continue;
        }

        if(pid == 0)//子进程运行区域
        {
            close(serv_sock);//在子进程中要关闭服务器套接字文件描述符
            while((str_len = read(clnt_sock, buf, BUF_SIZE)) != 0)
                write(clnt_sock, buf, str_len);
            
            close(clnt_sock);//执行完关闭自己的文件描述符
            puts("client disconnected...");
            return 0;
        }
        else//父进程运行区域
        {
            //调用fork函数后，要将无关的套接字描述符关闭掉
            close(clnt_sock);
        }
    }

    close(serv_sock);
    return 0;
}

void error_handling(const char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

//一旦有子进程结束就调用这个函数
void read_childproc(int sig)
{
    int status;
    pid_t id = waitpid(-1, &status, WNOHANG);//等待子进程终止
    if(WIFEXITED(status))
    {
        printf("remove proc id: %d\n", id);
        printf("child send: %d\n", WEXITSTATUS(status));
    }
}
