/*
filename server_ipaddress portno
argv[0] filename
argv[1] server_ipaddress
argv[2] portno
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <ctype.h>

char *trimwhitespace(char *str);

void error(const char *msg)
{
  perror(msg);
  exit(0);
}

int main(int argc, char *argv[])
{
  int sockfd, portno, n;
  struct sockaddr_in serv_addr;
  struct hostent *server;

  char buffer[255];
  if(argc < 3) {
    fprintf(stderr, "usage %s hostname port\n", argv[0]);
    exit(0);
  }

  portno = atoi(argv[2]);
  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  if (sockfd < 0)
    error("ERROR opening socket");

  puts("[-]Ensure you've paid social media tax before attempting a connection...");
  puts("[+]Socket created successfully...");

  server = gethostbyname(argv[1]);
  if(server == NULL) {
    fprintf(stderr, "ERROR, no such host\n");
    exit(1);
  }
  puts("[+]Attempting connection to server...");

  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  bcopy((char *)server ->h_addr,
        (char *)&serv_addr.sin_addr.s_addr,
        server -> h_length);

  serv_addr.sin_port = htons(portno);
  if(connect(sockfd,(struct sockaddr *) &serv_addr, sizeof(serv_addr))< 0)
    error("[-]Connection to server failed");

    puts("[+]Connected to server...");
    puts("[+]Please ensure to close your connection after your request, to enable others get their's processed faster.");
    puts("[+]Enter q to end the connection...");

  while(1)
  {
    printf("Client: ");
    bzero(buffer,255);
    fgets(buffer,255,stdin);

    if (buffer[0] == 'q') {
      close(sockfd);
      return 0;
    }
    n = write(sockfd,buffer,strlen(buffer));
    if(n < 0)
      error ("ERROR writing to socket");

    bzero(buffer,255);
    n = read(sockfd,buffer,255);
    if (n < 0)
      error("ERROR reading from socket");
    printf("Server: %s\n",buffer);
  }
  close(sockfd);
  return 0;
}