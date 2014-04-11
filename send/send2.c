#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
/*
  p+=sprintf(p,"POST /ddddd/av.openhome.org-Spotify-1/control HTTP/1.1\r\n");
  p+=sprintf(p,"Content-Type: text/xml; charset=\"utf-8\"\r\n");
  p+=sprintf(p,"SOAPACTION: \"urn:av-openhome-org:service:Spotify:1#Stop\"\r\n");
  p+=sprintf(p,"Content-Length: 213\r\n");//很重要
  p+=sprintf(p,"Connection: close\r\n");
  p+=sprintf(p,"Host: 192.168.1.113:50720\r\n");
  p+=sprintf(p,"\n\r");
  p+=sprintf(p,"<s:Envelope s:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\" xmlns:s=\"http://schemas.xmlsoap.org/soap/envelope/\"><s:Body><u:Stop xmlns:u=\"urn:av-openhome-org:service:Spotify:1\"/></s:Body></s:Envelope>");
*/
/*
  p+=sprintf(p,"POST /ddddd/av.openhome.org-Spotify-1/control HTTP/1.1\r\n");
  p+=sprintf(p,"Content-Type: text/xml; charset=\"utf-8\"\r\n");
  p+=sprintf(p,"SOAPACTION: \"urn:av-openhome-org:service:Spotify:1#Login\"\r\n");
  p+=sprintf(p,"Content-Length: 277\r\n");//很重要
  p+=sprintf(p,"Connection: close\r\n");
  p+=sprintf(p,"Host: 192.168.1.113:33949\r\n");
  p+=sprintf(p,"\n\r");
  p+=sprintf(p,"<s:Envelope s:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\" xmlns:s=\"http://schemas.xmlsoap.org/soap/envelope/\"><s:Body><u:Login xmlns:u=\"urn:av-openhome-org:service:Spotify:1\"><UserName>\"hello\"</UserName><PassWord>\"dddss\"</PassWord></u:Login></s:Body></s:Envelope>");
*/
/*
  p+=sprintf(p,"POST /ddddd/av.openhome.org-Spotify-1/control HTTP/1.1\r\n");
  p+=sprintf(p,"Content-Type: text/xml; charset=\"utf-8\"\r\n");
  p+=sprintf(p,"SOAPACTION: \"urn:av-openhome-org:service:Spotify:1#Play\"\r\n");
  p+=sprintf(p,"Content-Length: 239\r\n");//很重要
  p+=sprintf(p,"Connection: close\r\n");
  p+=sprintf(p,"Host: 192.168.1.113:33198\r\n");
  p+=sprintf(p,"\n\r");
  p+=sprintf(p,"<s:Envelope s:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\" xmlns:s=\"http://schemas.xmlsoap.org/soap/envelope/\"><s:Body><u:Play xmlns:u=\"urn:av-openhome-org:service:Spotify:1\"><Url>changpeng</Url></u:Play></s:Body></s:Envelope>");
  */
  int ConnectToTcpAddr(const char *hostname,int port)
{
  int sock;
  struct sockaddr_in addr;
  int one = 1;

  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
 // inet_pton(AF_INET,hostname,&addr.sin_addr);//另一种获取ip地址的方法
  {
    struct hostent *he;
    he = gethostbyname(hostname);
    addr.sin_addr = *(struct in_addr *)he->h_addr;
  }
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0) {
    perror(": ConnectToTcpAddr: socket");
    return -1;
  }
  if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
    perror(": ConnectToTcpAddr: connect");
    close(sock);
    return -1;
  }

  if (setsockopt(sock, IPPROTO_TCP, TCP_NODELAY,
		 (char *)&one, sizeof(one)) < 0) {
    perror(": ConnectToTcpAddr: setsockopt");
    close(sock);
    return -1;
  }
  return sock;
}
int
ConnectToServer(const char *hostname, int port)
{
    char buff[1024]={0};
  int rfbsock;
  struct hostent *hp;
  rfbsock = ConnectToTcpAddr(hostname,port);
  if (rfbsock < 0) {
    return -1;
  }
  char *p = buff;
  p+=sprintf(p,"POST /ddddd/av.openhome.org-Spotify-1/control HTTP/1.1\r\n");
  p+=sprintf(p,"Content-Type: text/xml; charset=\"utf-8\"\r\n");
  p+=sprintf(p,"SOAPACTION: \"urn:av-openhome-org:service:Spotify:1#Stop\"\r\n");
  p+=sprintf(p,"Content-Length: 213\r\n");//很重要
  p+=sprintf(p,"Connection: close\r\n");
  p+=sprintf(p,"Host: 192.168.1.113:50720\r\n");
  p+=sprintf(p,"\n\r");
  p+=sprintf(p,"<s:Envelope s:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\" xmlns:s=\"http://schemas.xmlsoap.org/soap/envelope/\"><s:Body><u:Stop xmlns:u=\"urn:av-openhome-org:service:Spotify:1\"/></s:Body></s:Envelope>");

  //  p+=sprintf(p,"\n\r \n\r");
    int n=write(rfbsock,buff,strlen(buff)+1);
 //   printf("%d\n",n);
    printf("%s\n",buff);
    char buf[10240]={0};
    int m = 0,totle=0;
    while(1)
    {
        if((m=read(rfbsock,buf,1024))>0)
        {
            totle+=m;
            printf("%s\n",buf);
            continue;
        }
        break;
    }
    printf("%d===========\n",totle);
    return 1;
}
int main(int argc,char *argv[])
{
    int port = atoi(argv[1]);
        ConnectToServer("192.168.1.113",port);
}
