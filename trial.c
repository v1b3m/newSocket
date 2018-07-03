
strcpy(new,strtok(NULL," "));
printf("%s\n",new );
// strcpy(new1,strtok(NULL," "));
// printf("%s\n",new1 );
//
// b[0] = atoi(strcpy(new2,strtok(new1,",")));
// printf("%d\n",b[0]);
// char new[50];
// char new1[50];
// char new2[20];
// // char ltr[1],ltr[2],ltr[3];
// char* word;
// int a[10];
// int b[10];
// int i=1;
//
// strcpy(new,strtok(NULL," "));
// printf("%s\n",new );
// strcpy(new1,strtok(NULL," "));
// printf("%s\n",new1 );
//
// b[0] = atoi(strcpy(new2,strtok(new1,",")));
// printf("%d\n",b[0]);
// bzero(new2,sizeof(new2));
//
// while((word = strtok(NULL,",")) != NULL) {
//   b[i] = atoi(word);
//   printf("%d",b[i]);
//   i++;  // bzero(new2,sizeof(new2));
//
// while((word = strtok(NULL,",")) != NULL) {
//   b[i] = atoi(word);
//   printf("%d",b[i]);
//   i++;
}
//
// //get the array size
// size_t n = sizeof(b)/sizeof(b[0]);
//
// //sort the array in ascending order
// for (int i = 0; i < n; i++)                     //Loop for ascending ordering
// {
// 	for (int j = 0; j < n; j++)             //Loop for comparing other values
// 	{
// 		if (b[j] > b[i])                //Comparing other array elements
// 		{
// 			int tmp = b[i];         //Using temporary variable for storing last value
// 			b[i] = b[j];            //replacing value
// 			b[j] = tmp;             //storing last value
// 		}
// 	}
// }
//
// i=0;
// for(int j=0;j<n;j++) {
//   del(new,b[j]-i);
//   i++;
// }

write(newsockfd, new,strlen(new));
