#include<stdio.h>
#include "def.h"

void affichage_plateau(cercle[9][9]tab){
  int k,i=8;
char [9] lettre={'I','H','F','G','E','D'};
//int [3] chiffre={9,8,7};

printf("%s\n","---------");

 for(k=0;k<6;k++){
   for(j=0;j<8;j++)
   
printf("%c %s %s\n",lettre[k] "/" tab[i][j]);
 i--;
 }

printf("%s %s %s\n", "c/" tab[j][] "/9");
printf("%s %s %s\n","B /" tab[j][] "/ 8");
printf("%s %s %s\n","A /" tab[j][] "/ 7");


printf("%s\n","---------  6");
printf("%s\n"," 1 2 3 4 5");
}



