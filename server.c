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
void strrev(unsigned char *str);
int itoa(int num, unsigned char* str, int len, int base);
char* encrypt(char * word,int size);
char* decrypt(char * word);


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
    } else if (strncmp("encrypt",message,7) == 0) {
      char word[256];
      char key[256];
      strcpy(word,strtok(NULL," "));
      trimwhitespace(word);
      int size = strlen(word);
      strcpy(key,encrypt(word,size));
      trimwhitespace(key);
      write(newsockfd, key ,256);
      bzero(key,256);
      bzero(word,256);
    } else if (strncmp("decrypt",message,7) == 0) {
      char word[50];
      char key[10];
      strcpy(word,strtok(NULL," "));
      trimwhitespace(word);
      strcpy(key,decrypt(word));
      trimwhitespace(key);
      write(newsockfd, key ,256);
      bzero(key,10);
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

char* encrypt(char * word,int size) {

  char *key = malloc(sizeof(char)*256);
  strcpy(key,"");
  char all_letters[53]=
  {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x'
  ,'y','z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V'
  ,'W','X','Y','Z','\0'};
  int substituteLetter[52]
  ={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,
    36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52};

  char * pointer2Letter;
  pointer2Letter = all_letters;

  int i;
    for (int i = 0; i < size; i++) {//This loops through the string
  		for (int j = 0; j < 53; j++) {//This goes over the array
  			if ( word[i] == pointer2Letter[j] ) {// This checks if the character is part of the array
  				int num[10];
          num[0] = substituteLetter[j];// This gets the value of the character
          num[1] = num[0] - 1;
          num[2] = num[0] - 9;
          num[3] = num[2] - 1;
          num[4] = num[2] - 9;

          if(num[0] > 18 && num[0] < 28) {
            int digit[2];
            int a;
            char n1[2];
            char n2[2];
            digit[0] = num[0] % 10;
            itoa(digit[0], n1, 2, 10);
            a = num[0] / 10;
            digit[1] = a % 10;

            itoa(digit[1], n2, 2, 10);

            char n3[2];
            n3[0] = all_letters[num[1]-1];
            n3[1] = '\0';

            //split num[2]
            char n4[2];
            char n5[2];
            int a1;
            digit[0] = num[2] % 10;
            itoa(digit[0], n4, 2, 10);
            a1 = num[2] / 10;
            digit[1] = a1 % 10;
            itoa(digit[1], n5, 2, 10);

            char n6[2];
            n6[0] = all_letters[num[3]-1];
            n6[1] = '\0';

            int n,count = 0;
            n = num[4];

            while (n != 0){
              n /= 10;
              ++count;
            }

            char n7[2];
            if(count = 1){

              n7[0] = all_letters[num[4]+25];
              n7[1] = '\0';
            }
            strcat(key,n2);
            strcat(key,n3);
            strcat(key,n5);
            strcat(key,n7);
            strcat(key,n6);
            strcat(key,n4);
            strcat(key,n1);
          } else if (num[0] < 10) {
            int i = num[0] + 25;
            char n[2];
            n[0] = all_letters[i];
            n[1] = '\0';
            strcat(key,n);
          } else if (num[0] > 9 && num[0] < 19) {
            int i = num[0] + 24;
            char n[2];
            n[0] = all_letters[i];
            n[1] = '\0';

            char n1[2];
            char n2[2];
            int j,digit[2];
            digit[0] = num[0] % 10;
            itoa(digit[0], n1, 2, 10);
            j = num[0] / 10;
            digit[1] = j % 10;
            itoa(digit[1], n2, 2, 10);

            strcat(key,n2);
            strcat(key,n);
            strcat(key,n1);

          } else if (num[0] > 27 && num[0] < 45 ) {
            char n1[2];
            char n2[2];
            int j,digit[2];
            digit[0] = num[0] % 10;
            itoa(digit[0], n1, 2, 10);
            j = num[0] / 10;
            digit[1] = j % 10;
            itoa(digit[1], n2, 2, 10);

            int i = num[0] - 28;
            char n[2];
            n[0] = all_letters[i];
            n[1] = '\0';

            char n3[2];
            char n4[2];
            int num_3 = num[0] - 9;
            digit[0] = num_3 % 10;
            itoa(digit[0], n3, 2, 10);
            j = num_3 / 10;
            digit[1] = j % 10;
            itoa(digit[1], n4, 2, 10);

            int num_4 = num_3 - 1;
            char n5[2];
            n5[0] = all_letters[num_4-1];
            n5[1] = '\0';

            int num_5 = num_3 + 17;
            char n6[2];
            n6[0] = all_letters[num_5-1];
            n6[1] = '\0';

            strcat(key,n2);
            strcat(key,n);
            strcat(key,n4);
            strcat(key,n6);
            strcat(key,n5);
            strcat(key,n3);
            strcat(key,n1);
          } else if (num[0] > 44) {
            int num8 = num[0] - 27;

            //split the number
            char one[2];
            char two[2];
            char four0[2];
            char four1[1];
            int digit[2],j,numa;
            digit[0] = num[0] % 10;
            numa = num[0] - 9;
            itoa(digit[0], two, 2, 10);
            j = num[0] / 10;
            digit[1] = j % 10;
            itoa(digit[1], one, 2, 10);

            char three[2];
            three[0] = all_letters[num8-1];
            three[1] = '\0';

            digit[0] = numa % 10;
            itoa(digit[0], four1, 2, 10);
            j = numa / 10;
            digit[1] = j % 10;
            itoa(digit[1], four0, 2, 10);

            int numb = numa - 1;
            char five[2];
            five[0] = all_letters[numb-1];
            five[1] = '\0';

            int numc = numa - 9;
            char six[2];
            six[0] = all_letters[numc-1];
            six[1] = '\0';

            strcat(key,one);
            strcat(key,three);
            strcat(key,four0);
            strcat(key,six);
            strcat(key,five);
            strcat(key,four1);
            strcat(key,two);
          }
  			}
  		}
  	}
    trimwhitespace(key);
    printf("%s\n",key );
	  return key;
  }

  int itoa(int num, unsigned char* str, int len, int base)
  {
  	int sum = num;
  	int i = 0;
  	int digit;
  	if (len == 0)
  		return -1;
  	do
  	{
  		digit = sum % base;
  		if (digit < 0xA)
  			str[i++] = '0' + digit;
  		else
  			str[i++] = 'A' + digit - 0xA;
  		sum /= base;
  	}while (sum && (i < (len - 1)));
  	if (i == (len - 1) && sum)
  		return -1;
  	str[i] = '\0';
  	strrev(str);
  	return 0;
  }

  char* decrypt(char * word) {
    char all_letters[53]=
    {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x'
    ,'y','z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V'
    ,'W','X','Y','Z','\0'};
    int substituteLetter[52]
    ={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,
      36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52};
    char * key = malloc(sizeof(char)*2);
  	strcpy(key,"");
  	for (int i = 0; i < 52; i++) {//This loops over the array with the characters
      char letter[2];
      letter[0] = all_letters[i];
      letter[1] = '\0';

  		if (strcmp(word,encrypt(letter,1)) == 0) {//This then inserts every letter in the array in the encrypt function until it matches that of the string  we hav put in
        strcat(key,letter);
        trimwhitespace(key);
        break;
  		}
  	}
  	return key;
  }


void strrev(unsigned char *str)
  {
  	int i;
  	int j;
  	unsigned char a;
  	unsigned len = strlen((const char *)str);
  	for (i = 0, j = len - 1; i < j; i++, j--)
  	{
  		a = str[i];
  		str[i] = str[j];
  		str[j] = a;
  	}
  }
