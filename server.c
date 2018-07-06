/* A simple  server in the internet domain using TCP
  The port number is passed as an argument */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>
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
char *trimwhitespace(char *str);


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
    fp = fopen("ready_jobs.txt","a");
    char message[255];
    char* word;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    // printf("now: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
    // tm.tm_hour,tm.tm_min, tm.tm_sec);

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
      int i, j, temp;
      int l = strlen(word);


        for (i = 0, j = l - 1; i < j; i++, j--) {
        temp = word[i];
        word[i] = word[j];
        word[j] = temp;
        }
        word = trimwhitespace(word);
        clock_t end = clock();
        double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        n = write(newsockfd, word ,strlen(word));

        if (n < 0 ) {
    			error("Error on writing");
        } else {
          fprintf(fp,"rev,%f,%d-%d-%d %d:%d:%d\n", time_spent,tm.tm_year + 1900,
          tm.tm_mon + 1, tm.tm_mday, tm.tm_hour,tm.tm_min, tm.tm_sec);
          bzero(word,sizeof(word));
        }

    } else if (strncmp("dbl",message,3) == 0)
    {
      clock_t begin = clock();
      word = strtok(NULL," ");
      dbl(word);
      clock_t end = clock();
      n = write(newsockfd, word ,strlen(word));

      if (n < 0 ) {
        error("Error on writing");
      } else {
      double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
      fprintf(fp,"dbl,%f,%d-%d-%d %d:%d:%d\n", time_spent,tm.tm_year + 1900,
      tm.tm_mon + 1, tm.tm_mday, tm.tm_hour,tm.tm_min, tm.tm_sec);
      bzero(word,sizeof(word));
    }
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


    n = write(newsockfd, word ,sizeof(word));
    if (n < 0 ) {
      error("Error on writing");
    } else {
      double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
      fprintf(fp,"del,%f,%d-%d-%d %d:%d:%d\n", time_spent,tm.tm_year + 1900,
      tm.tm_mon + 1, tm.tm_mday, tm.tm_hour,tm.tm_min, tm.tm_sec);
    }
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
      // p[index] = letter;

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
  //close the send socket-this frees up memory
  close(newsockfd);
  //close the connection socket
  close(sockfd);
  return 0;


}



//this is the method to double the strings
void dbl(char s[]) {
  char* a;
  strcpy(a,s);
  trimwhitespace(a);
  trimwhitespace(s);
  trimwhitespace(strcat(s,a));
}

//this is the method to delete characters from strings
void del(char word[],int i) {
    memmove(&word[i], &word[i + 1], strlen(word) - i);
}

char *trimwhitespace(char *str)
{
  char *end;

  // Trim leading space
  while(isspace((unsigned char)*str)) str++;

  if(*str == 0)  // All spaces?
    return str;

  // Trim trailing space
  end = str + strlen(str) - 1;
  while(end > str && isspace((unsigned char)*end)) end--;

  // Write new null terminator character
  end[1] = '\0';

  return str;
}
