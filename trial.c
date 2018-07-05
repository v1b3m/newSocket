#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
char word[50];
char replacements[50];
char a[4];
char b[4];
char c[4];
char d[4];
char e[4];

int index;
char letter[1];
char *p = word;

printf("Enter the job:");
scanf("%s",word );
printf("%s\n",word );

strcpy(replacements,strtok(word,", "));
printf("%s\n",replacements );

strcpy(a,strtok(replacements, ","));
printf("%s\n",a );

index = atoi(strtok(a,"-"));
printf("%d\n",index );
strcpy(letter,strtok(NULL,"-"));
printf("%s\n",letter );

p[index] = letter;
printf("%s\n",word );
}
