#include <stdio.h>
#include <arpa/inet.h>
#include <string>
#include <unistd.h>
int main()
{
    //1.创建用于监听的Socket
    int lfd=socket(AF_INET,SOCK_STREAM,0);

    if(lfd==-1)
    {
        perror("socket");
        exit(-1);
    }

    //2.绑定
    struct sockaddr_in saddr;
    saddr.sin_family=AF_INET;//协议
    //inet_pton(AF_INET,"192.168.71.129",saddr.sin_addr.s_addr);//地址
    saddr.sin_addr.s_addr=INADDR_ANY;//任意地址 
    saddr.sin_port=htons(9999);//端口
    int ret=bind(lfd,(struct sockaddr*)&saddr,sizeof(saddr));
    if(ret==-1)
    {
        perror("bind");
        exit(-1);
    }
    //3.监听
    ret=listen(lfd,8);
    if(ret==-1)
    {
        perror("listen");
        exit(-1);
    }
    //4.接收客户端的连接
    struct sockaddr_in client_addr;
    socklen_t len=sizeof(client_addr);
    int cfd=accept(lfd,(struct sockaddr*)&client_addr,&len);
    if(cfd==-1)
    {
        perror("accept");
        exit(-1);
    }
    //输出客户端的信息
    char clientIP[16];
    inet_ntop(AF_INET,&client_addr.sin_addr.s_addr,clientIP,sizeof(clientIP));
    unsigned short clientPort=ntohs(client_addr.sin_port);
    printf("client ip is %s, port is %d\n",clientIP,clientPort);
    //5.获取客户端数据
    char recvBuf[1024]={0};
    int len=read(cfd,recvBuf,sizeof(recvBuf));
    if(len==-1)
    {
        perror("read");
        exit(-1);
    }
    else if(len>0) printf("client data:%d",recvBuf);
    else printf("client closed...");
    char * data="hello,I am server";
    write(cfd,*data,strlen(data));
    //关闭文件描述符
    close(cfd);
    close(lfd);
    return 0;
}