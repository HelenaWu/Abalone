#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include"../def.h"
#include "mise_a_jour.h"
#include"verifie_coup.h"
#include "../Analyse/lecture_fichier.h"

enum direction{NW=1, NE=2, E=3, SE=4, SW=5, W=6, ERR=7};


int* verifie_coup(int * resultat, cercle_t * cercles, int direction, jeux_t jeux){
  //revoie resultat
  
  printf("entre dans verifie_coup.\n");
  printf("dir est: %d\n", direction);

    
  if(cercles[0]->etat==0){
    fprintf(stderr, "c'est vide! reessayez une autre commande!");
    return 1;
  }

  /*---compter nombre de cercles---*/
  int compteur=0;
  while(cercles[compteur]!=NULL){
    compteur++;

  }

  /*---initialise resultat---*/
  int i;

  for(i=0; i<6; i++){
    resultat[i] = 0;
  }
    
  if(compteur == 1){
    resultat = recurse_verifie(resultat,cercles[0], direction, jeux);
  }
  if(compteur == 3){

    //....../
  }
  
  /*---erreur quelque part---*/
  if(resultat[4] == 1){
    perror("Votre commande n'est pas valide, reessayez.\n");
    //error code?
  }
  printf("resultat: %d, %d, %d, %d, %d, %d\n", resultat[0],  resultat[1],  resultat[2],  resultat[3], resultat[4], resultat[5]);
  return resultat;
}


int * recurse_verifie(int * resultat, cercle_t cercle, int  direction, jeux_t jeux){
  //resultat[0] = noir en train d'etre pousser, resultat[1] = blanc, resultat[2] = noir sortis, resultat[3] = blanc sortis, resultat[4] = etat program, init. a 0, si rencontrer un erreur, mise a 1; resultat[5] =etat couleur

 
 
  /*---on rencontre un espace vide---*/
  if(cercle->etat == 0){
    printf("on rencontre un espace vide\n");
    return resultat;
  }
 

 /*---decide couleur de cercle courant---*/
  if(cercle->couleur=='N'){
   
    resultat[0]++;
  }
  if(cercle->couleur == 'B'){
    resultat[1]++;
  }

  /*---quelqu'un a gagne---*/
  if(resultat[2] == 6){
    printf("felicitation! Blanc a gagne!\n");
    exit(0);
  }
  if(resultat[3]==6){
    printf("felicitation! Noir a gagne!\n");
    exit(0);
  }

  /*---on va depasser le nombre limite de billes a pousser---*/
  if(resultat[0] >=4 || resultat[1] >= 4){
    printf("on va depasser le nombre limite de billes a pousser.\n");
    resultat[4]  = 1; //flag que verification a echoue
    return resultat;
  }
  
  /*---verifie si on a une sequence valide de couleur---*/
  resultat[5]=valide_couleur(resultat[5], cercle);
  if(resultat[5] == 5){
    resultat[4]  = 1;
    perror("il y a un sandwich.");
    return resultat;
  }
  
  /*---on va depasser le plateau---*/
  /*2 cas:on sort une bille si possible, ou error  */
  regle_t regle = cercle->regle;
  
  // afficheCercle(cercle);
  printf("le cas est: %d\n", regle->cas);
  printf("%c \n", regle->NW);
  printf("%c \n", regle->NE);
  printf("%c \n", regle->E);
  printf("%c \n", regle->SE);
  printf("%c \n", regle->SW);
  printf("%c \n", regle->W);
  printf("/--------------/");  







  if(dir_int_to_char(regle,direction) == 'x'){
    if(resultat[5] == 3 || resultat[5] == 4){
      int gauche, droit;
      if(cercle->couleur =='B'){
	gauche = resultat[0];
	droit = resultat[1];
      }
      if(cercle->couleur =='N'){
	gauche = resultat[1];
	droit = resultat[0];
      }
      if((gauche-droit)>=1){
	//pousser la derniere bille
	resultat = sort_bille(resultat, cercle);
	return resultat;
	
      }else{
	printf("on ne peut pas faire sortir la bille. \n");
	resultat[4] =1;
	return resultat;
      }
    }
    else{
      printf("vous essayez de poussez votre propre bille. Recommencez.\n");
      resultat[4]  = 1;
      return resultat;
    }
  }



    
    char * nom_prochain = nouvelle_position(cercle->nom, direction);
    cercle_t bille_prochaine = nom_to_bille(nom_prochain, jeux); 
    resultat  = recurse_verifie(resultat, bille_prochaine,  direction, jeux);

     if(resultat[4] !=1){
       deplace_bille(cercle,bille_prochaine);
    }
    
    return resultat;

}


char * nouvelle_position(char* nom_courant, int direction){
  //NW=1, NE=2, E=3, SE=4, SW=5, W=6, ERR=7
  char *nom_prochain = nom_courant;

  switch(direction){
  case NW:
    nom_prochain[0] = (nom_courant[0] + 1);
    break;
  case NE:
    nom_prochain[0] = (nom_courant[0] + 1);
    nom_prochain[1] = (nom_courant[1] + 1);
    break;
  case E:
    nom_prochain[1] = (nom_courant[1] + 1);
    break;
  case SE:
    nom_prochain[0] = (nom_courant[0] - 1);
    break;
  case SW:
    nom_prochain[0] = (nom_courant[0] - 1);
    nom_prochain[1] = (nom_courant[1] - 1);
    break;
  case W:
    nom_prochain[1] = (nom_courant[1] - 1);
    break;
  default:
    fprintf(stderr,"on ne comprend pas la direction: %d\n", direction);
  }
  return nom_prochain;
}

int valide_couleur(int couleur_etat, cercle_t c){
  /*cette fonction permet de verifier les couleurs de toute la ligne qui correspond a la commande entree par l'utilisateur
  case: 1=> on n'a que des billes de couleur noir, 2 => que des blanches , 3 => les 2, et la derniere est noir, 4=> les 2,
  et la derniere est blanche, 5=> on a un 'sandwich'
  */
  int new_etat = couleur_etat;
  switch(couleur_etat){
  case 0:
    if(c->couleur == 'B'){
      new_etat = 2;
    }
    if(c->couleur =='N'){
      new_etat = 1;
    }
    break;
  case 1:
    if(c->couleur == 'B')
      new_etat = 4; 
      break;
  case 2:
    if(c->couleur =='N')
      new_etat = 3;
    break;
  case 3:
    if(c->couleur == 'B')
      new_etat =5;
    break;
  case 4:
    if(c->couleur =='N')
      new_etat =5;
    break;
  default:
    fprintf(stderr,"couleur etat invalide %d\n",couleur_etat); 
    
  }
  return new_etat;

}
char  dir_int_to_char(regle_t regle, int direction){
  switch(direction){
  case NW:
    return regle->NW;
    break;
  case NE:
    return regle->NE;
    break;
  case E:
    return regle->E;
    break;
  case SE:
    return regle->SE;
    break;
  case SW:
    return regle->SW;
    break;
  case W:
    return regle->W;
    break;
  default:
    fprintf(stderr,"il n'y a pas de regle: %d\n", direction);
  }
}



