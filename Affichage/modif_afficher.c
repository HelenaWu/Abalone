#include <stdio.h>

int main(){
  
  char *t[]={"I5","I6","I7","I8","I9","H4","H5","H6","H7","H8","H9","G3","G4","G5","G6","G7","G8","G9","F2","F3","F4","F5","F6","F7","F8","F9","E1","E2","E3","E4","E5","E6","E7","E8","E9","D1","D2","D3","D4","D5","D6","D7","D8","C1","C2","C3","C4","C5","C6","C7","B1","B2","B3","B4","B5","B6","A1","A2","A3","A4","A5"};
  int i;
 printf("       --------------\n"); 
  printf("    I/ ");
  for( i=0;i<5;i++)
  printf("%s ",t[i]);
  printf("\\\n");
  

 printf("   H/");
 for( i=5;i<11;i++)
  printf("%s ",t[i]);
 printf("\\\n");

 printf("  G/");
for( i=11;i<18;i++)
  printf("%s ",t[i]);
 printf("\\\n");
 
printf(" F/");
for( i=18;i<26;i++)
  printf("%s ",t[i]);
 printf("\\\n");

printf("E ");
for( i=26;i<35;i++)
  printf("%s ",t[i]);
 printf(" \n");

printf(" D\\");
for( i=35;i<43;i++)
  printf("%s ",t[i]);
 printf("/9\n");

 //printf("C\\  ");
printf("  C\\");
for( i=43;i<50;i++)
  printf("%s ",t[i]);
 printf("/8\n");

 //printf("B\\   ");
printf("   B\\");
for( i=50;i<56;i++)
  printf("%s ",t[i]);
 printf("/7\n");

 //printf("A\\    ");
printf("    A\\");
for( i=56;i<61;i++)
  printf("%s ",t[i]);
 printf("/6\n");

 printf("       --------------\n");
 printf("       1  2  3  4  5\n");







}
