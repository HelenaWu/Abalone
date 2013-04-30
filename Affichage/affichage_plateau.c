#include<stdio.h>
#include "../def.h"
#include "../Analyse/lecture_fichier.h"
#include "affichage_plateau.h" 


#define NOMBRE_CERCLES 61

void affichage_plateau(jeux_t jeux){
  cercle_t * plateau = jeux->plateau;
  printf("       ---------    \n");
  printf("     I/%c%c%c%c%c\   \n",nc(plateau, "I5"), nc(plateau, "I6"),nc(plateau, "I7"),nc(plateau, "I8"),nc(plateau, "I9") );

}

char nc (cercle_t * plateau, char* nom){
  char res;
  int indice = hash_nom(nom[0], nom[1], NOMBRE_CERCLES);
  res = plateau[indice]->suivant->couleur;
  return res;


}
