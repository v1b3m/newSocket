#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

int itoa(int num, unsigned char* str, int len, int base);
void strrev(unsigned char *str);

char* main(int argc, char * argv[]) {
  if(argc < 2 ) {
    printf("Please enter a string to encrypt\n");
    exit(0);
  }

  char *key = malloc(sizeof(char)*256);
  char all_letters[53]=
  {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x'
  ,'y','z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V'
  ,'W','X','Y','Z','\0'};
  int substituteLetter[52]
  ={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,
    36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52};

  char * pointer2Letter;
  pointer2Letter = all_letters;
  char * a;
  a = key;
  char word[50];
  strcpy(word,argv[1]);
  char * p;
  p = word;
  int size = strlen(p);

  int i;
    for (int i = 0; i < size; i++) {//This loops through the string
  		for (int j = 0; j < 53; j++) {//This goes over the array
  			if ( p[i] == pointer2Letter[j] ) {// This checks if the character is part of the array
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
            printf("%s\n",key );
          } else if (num[0] < 10) {
            int i = num[0] + 25;
            char n[2];
            n[0] = all_letters[i];
            n[1] = '\0';
            strcat(key,n);
            printf("%s\n",key );
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
            printf("%s\n",key );

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
            printf("%s\n",key );
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
            printf("%s\n",key );
          }
  			}
  		}
  	}
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

  void
  strrev(unsigned char *str)
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
