#include<stdio.h>
#include<stdlib.h>


char * prochain_mot(FILE *f){
  char * buf = malloc(101);
  if(fscanf(f, " %s", buf)){
      return buf;
    }else{
      return NULL;
  }
}

/* jeux  parse(char* nom_fichier){ */
/*   FILE *f = fopen(nom_fichier, "r+"); */
/*   char * joueur = prochain_mot(f); */
/*   if(strcmp(joueur,"N")==1 || strcmp(joueur, "B")==1){ */
/*     printf("retaper nom_joeur"); */
/*     Exit(1); */
/*   } */
/*   int c_blanc = prochain_mot(f); */
/*   int c_noir = prochain_mot(f); */
  
/*   typedef struct jeux { */
/*     char * joueur; */
/*     int c_blanc; */
/*     int c_noir; */
/*     Cercle[9][9] plateau; */
 

/* } */


int main (int argc, char * argv[]){
  FILE *f1 = fopen(argv[1], "r+");
  int i;
  
  char * mot=prochain_mot(f1);
  while(!feof(f1)){
 
    printf("mot est %s\n", mot);
    mot=prochain_mot(f1);
 
  }
  return 0;

}




