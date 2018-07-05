/* A simple  server in the internet domain using TCP
  The port number is passed as an argument */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg)
{
  perror(msg);
  exit(1);
}
void reverse(char s[]);
void dbl(char s[]);
void del(char word[],int i);


//int argc is the total number of parameters we'll be passing
int main(int argc, char *argv[])
{
  if(argc < 2) {
    fprintf(stderr, "[-]ERROR, no Port number provided, program terminated\n");
    exit(1);
  }

  int sockfd, newsockfd, portno, n;
  char buffer[255];

  struct sockaddr_in serv_addr, cli_addr;
  socklen_t clilen;

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
    error("[-]ERROR opening socket");

  //clears everything in the specified field so that it is clear before we input any
  //data_to_send, here it clears the server address
  bzero((char *)&serv_addr, sizeof(serv_addr));

  portno = atoi(argv[1]);//second input from keyboard

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(portno);

  if(bind(sockfd , (struct sockaddr *) &serv_addr ,sizeof(serv_addr) ))
    error("Binding failed");

  listen(sockfd ,5);
  clilen = sizeof(cli_addr);

  newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

  if(newsockfd < 0)
    error("Error on accept");


  while(1)
  {
    FILE * fp;
    fp = fopen("log.txt","w");
    fprintf(fp,"We're up");
    char message[255];
    char* word;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    printf("now: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour,
    tm.tm_min, tm.tm_sec);

    bzero(buffer, 255);
    n = read(newsockfd, buffer, 255);
    if(n < 0)
      error("Error on reading.");

    printf("Client: %s\n",buffer);
    strcpy(message,buffer);
    word = strtok(message," ");

    //reversing the function
    int a;
    if(strncmp("rev",message,3) == 0)
    {
        clock_t begin = clock();
        word = strtok(NULL," ");
        reverse(word);
        clock_t end = clock();
        double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        printf("%f\n",time_spent );
        n = write(newsockfd, word ,strlen(word));
        if (n < 0 )
    			error("Error on writing");
        bzero(word,sizeof(word));
    } else if (strncmp("dbl",message,3) == 0)
    {
      clock_t begin = clock();
      word = strtok(NULL," ");
      dbl(word);
      clock_t end = clock();
      write(newsockfd, word ,strlen(word));
      double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
      bzero(word,sizeof(word));
    } else if (strncmp("del",message,3) == 0)
    {
      clock_t begin = clock();
      char word[50];
      char numbers[20];

      //initialize array to hold the indexes to be deleted
      int num[10]={0};

      strcpy(word,strtok(NULL," "));
      strcpy(numbers,strtok(NULL," "));

      int n = strlen(numbers);

      num[0] = atoi(strtok(numbers,","));
      printf("%d\n",num[0] );

      for(int i=1;i<(n/2);i++) {
        num[i] = atoi(strtok(NULL,","));
      }

      // sort the array in ascending order
      for (int i = 0; i < 10; i++)                     //Loop for ascending ordering
      {
      	for (int j = 0; j < 10; j++)             //Loop for comparing other values
      	{
      		if (num[j] > num[i])                //Comparing other array elements
      		{
      			int tmp = num[i];         //Using temporary variable for storing last value
      			num[i] = num[j];            //replacing value
      			num[j] = tmp;             //storing last value
      		}
      	}
      }

    int j=1;
    for(int i=0;i<10;i++){
      if(num[i] != 0) {
        del(word,num[i]-j);
        j++;
      }
    }
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

      write(newsockfd, word ,sizeof(word));
    } else if (strncmp("rep",message,3) == 0)
    {
      char word[50];
      char replacements[50];

      int index;
      char letter[1];



      strcpy(word,strtok(NULL," "));
      strcpy(replacements,strtok(NULL," "));

      index = atoi(strtok(replacements,"-"));
      strcpy(letter,strtok(NULL,"-"));

      char* p = word;
      p[index] = letter;

      //replace the character

      write(newsockfd, p ,sizeof(p));
      bzero(word, 50);
      bzero(replacements,50);
      bzero(letter,1);
    }

    //reads bytes in a string into the buffer pointed to by the first parameter
    //    fgets(buffer , 255 ,stdin);
    int i = strncmp("Bye" , buffer , 3);
    if(i == 0)
    break;
    fclose(fp);
  }
  
  close(newsockfd);
  close(sockfd);
  return 0;

  }

  void reverse(char s[])
  {
      void reverser(char s[],int i,int len);

      reverser(s,0,strlen(s));
  }

  /* reverser: reverse string s in place; recursive */

  void reverser(char s[],int i,int len)
  {
      int c,j;

      j = len - (i + 1);

      if( i < j )
      {
          c = s[i];
          s[i] = s[j];
          s[j] = c;

          reverser(s,++i,len);
      }
  }

void dbl(char s[]) {
  char* a;
  strcpy(a,s);
  strcat(s,a);
}

void del(char word[],int i) {
    memmove(&word[i], &word[i + 1], strlen(word) - i);
}
