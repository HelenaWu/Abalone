#include<stdio.h>
#include "../def.h"
#include "mise_a_jour.h"


int * sort_bille(int *resultat, cercle_t c_courant){
  char couleur = c_courant->couleur;
  if(couleur =='N'){
    resultat[2]++;
  }else{
    resultat[3]++;
  }
  c_courant->etat =0;
  c_courant->couleur = '.';
  return resultat;
}


void deplace_bille(cercle_t c_courant, cercle_t c_prochain){
  char couleur_tmp;
  int etat_tmp;

  couleur_tmp =c_courant->couleur;
  etat_tmp = c_courant->etat;
  c_courant->couleur = c_prochain->couleur;
  c_courant->etat = c_prochain->etat;
  
  c_prochain->couleur =  couleur_tmp;
  c_prochain->etat = etat_tmp;

}
