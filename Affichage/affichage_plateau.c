#include<stdio.h>
#include<string.h>
#include "../def.h"
#include "../Analyse/lecture_fichier.h"
#include "affichage_plateau.h" 


#define NOMBRE_CERCLES 61

void affichage_plateau(jeux_t jeux){

/* char *t[]={"I5","I6","I7","I8","I9","H4","H5","H6","H7","H8","H9","G3","G4","G5","G6","G7","G8","G9","F2","F3","F4","F5","F6","F7","F8","F9","E1","E2","E3","E4","E5","E6","E7","E8","E9","D1","D2","D3","D4","D5","D6","D7","D8","C1","C2","C3","C4","C5","C6","C7","B1","B2","B3","B4","B5","B6","A1","A2","A3","A4","A5"}; */
/*   int i; */
/*  printf("       ----------\n");  */
/*   printf("    I/ "); */
/*   for( i=0;i<5;i++) */
/*     printf("%c ",nc(jeux,t[i])); */
/*   printf("\\\n"); */
  

/*  printf("   H/"); */
/*  for( i=5;i<11;i++) */
/*    printf("%c ",nc(jeux,t[i])); */
/*  printf("\\\n"); */

/*  printf("  G/"); */
/* for( i=11;i<18;i++) */
/*   printf("%c ",nc(jeux,t[i])); */
/*  printf("\\\n"); */
 
/* printf(" F/"); */
/* for( i=18;i<26;i++) */
/*   printf("%c ",nc(jeux,t[i])); */
/*  printf("\\\n"); */

/* printf("E "); */
/* for( i=26;i<35;i++) */
/*   printf("%c ",nc(jeux,t[i])); */
/*  printf(" \n"); */

/* printf(" D\\"); */
/* for( i=35;i<43;i++) */
/*   printf("%c ",nc(jeux,t[i])); */
/*  printf("/9\n"); */

/*  //printf("C\\  "); */
/* printf("  C\\"); */
/* for( i=43;i<50;i++) */
/*   printf("%c ",nc(jeux,t[i])); */
/*  printf("/8\n"); */

/*  //printf("B\\   "); */
/* printf("   B\\"); */
/* for( i=50;i<56;i++) */
/*   printf("%c ",nc(jeux,t[i])); */
/*  printf("/7\n"); */

/*  //printf("A\\    "); */
/* printf("    A\\"); */
/* for( i=56;i<61;i++) */
/*   printf("%c ",nc(jeux,t[i])); */
/*  printf("/6\n"); */

/*  printf("       ---------\n"); */
/*  printf("       1 2 3 4 5\n"); */






  printf("\n        -----------    \n");
  printf("     I / %c %c %c %c %c \\   \n",nc(jeux, "I5"), nc(jeux, "I6"),nc(jeux, "I7"),nc(jeux, "I8"),nc(jeux, "I9") );
  printf("    H / %c %c %c %c %c %c \\   \n",nc(jeux, "H4"), nc(jeux, "H5"),nc(jeux, "H6"),nc(jeux, "H7"),nc(jeux, "H8") ,nc(jeux, "H9"));
  printf("   G / %c %c %c %c %c %c %c \\   \n",nc(jeux, "G3"), nc(jeux, "G4"),nc(jeux, "G5"),nc(jeux, "G6"),nc(jeux, "G7"),nc(jeux, "G8"),nc(jeux, "G9") );
  printf("  F / %c %c %c %c %c %c %c %c \\   \n",nc(jeux, "F2"), nc(jeux, "F3"),nc(jeux, "F4"),nc(jeux, "F5"),nc(jeux, "F6"),nc(jeux, "F7"),nc(jeux, "F8"),nc(jeux, "F9") );
  printf(" E   %c %c %c %c %c %c %c %c %c \\   \n",nc(jeux, "E1"), nc(jeux, "E2"),nc(jeux, "E3"),nc(jeux, "E4"),nc(jeux, "E5"),nc(jeux, "E6"),nc(jeux, "E7"),nc(jeux, "E8"),nc(jeux, "E9"));
  printf("  D \\ %c %c %c %c %c %c %c %c /9  \n",nc(jeux, "D1"), nc(jeux, "D2"),nc(jeux, "D3"),nc(jeux, "D4"),nc(jeux, "D5"),nc(jeux, "D6"),nc(jeux, "D7"),nc(jeux, "D8"));
  printf("   C \\ %c %c %c %c %c %c %c /8 \n",nc(jeux, "C1"), nc(jeux, "C2"),nc(jeux, "C3"),nc(jeux, "C4"),nc(jeux, "C5"),nc(jeux, "C6"),nc(jeux, "C7") );
  printf("    B \\ %c %c %c %c %c %c /7  \n",nc(jeux, "B1"), nc(jeux, "B2"),nc(jeux, "B3"),nc(jeux, "B4"),nc(jeux, "B5") ,nc(jeux, "B6"));
  printf("     A \\ %c %c %c %c %c /6  \n",nc(jeux, "A1"), nc(jeux, "A2"),nc(jeux, "A3"),nc(jeux, "A4"),nc(jeux, "A5") );
  printf("         ----------  \n");
  printf("          1 2 3 4 5\n");
}

char nc (jeux_t jeux, char* nom){
  char res;


  liste_nom_t tmp_l =jeux->hash_nom[hash_nom(nom[0],nom[1], NOMBRE_CERCLES)]; 
  

  while(strcmp(tmp_l->cle, nom)!=0){
    tmp_l = tmp_l->suivant;
  }
  

  int indice = tmp_l->indice;
  
  
  res = jeux->plateau[indice]->couleur;
  //printf("res: %c\n", res);
 
  


  // printf("resultat cercle couleur => %c, nom => %s\n", res, jeux->plateau[indice]->nom);
  return res;


}


