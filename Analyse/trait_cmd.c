#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include  "../def.h"
#include"lecture_fichier.h"
#include"trait_cmd.h"


#define TAILLE 11
enum direction{NW=1, NE=2, E=3, SE=4, SW=5, W=6, ERR=7};

/*
Cette Class:
  1) Prend cmd depuis la ligne de cmd
  2) Verfie la validite de la cmd
  3) Prend plateau depuis analyse||lecture_fichier.c, renvoie le/les cercles concernant + direction de mvt 
  => computation
*/

int verifie_cmd(char * cmd, int len){
  /*return 1 si echoue*/
  int n;
  int indice=0;
  for(n=0; n<3; n++){
 

    if(!(cmd[indice]<='I' && cmd[indice]>='A'&& cmd[indice+1]<='9' && cmd[indice+1] >='1')){
      printf("rate a %d %d n= %d\n", cmd[indice], cmd[indice+1],n);
      fprintf(stderr, "mauvaise cmd %s", cmd);
      return 1;
    }
    if(n==0){
      if(!(cmd[2]=='-')){
	return 1;
      }
    }
 
    if(n==1){
      if(len==7){
	if(!(cmd[5]=='*')){
	  return 1;
	}
      }

      if(len==7 || len==6){
	return 0;
      }
     
      if(len==9 || len==10){
	if(!(cmd[5]=='-')){
	  return 1;
	}
      }
    }
    indice=indice+3;
    if(n==2){
      if(len==10){
	if(!(cmd[8]=='*')){
	  return 1;
	}
      }
      return 0;
    }
   
  }
}



int dir_mvt(char * cmd){
int len = strlen(cmd);
 len+=1;
    char d_1 = cmd[0];
    char d_2 = cmd[1];
    char f_1;
    char f_2;
    printf("len dans dir_mvt est: %d\n", len);
   switch(len){
   case 6:
   case 7:
    f_1 = cmd[3];
    f_2 = cmd[4];
    break;
   case 9:
   case 10:
    f_1 = cmd[6];
    f_2 = cmd[7];
    break;
   }
     printf("d_1 = %d; d_2 = %d; f_1 = %d; f_2 = %d\n", d_1, d_2, f_1, f_2);
  int diff_1 = f_1 - d_1;
  int diff_2 = f_2 - d_2;
  int dir = direction(diff_1, diff_2);
  return dir; 

}

int direction(int diff_1, int diff_2){
  int dir;
  printf("diff-1 = %d, diff-2= %d\n",diff_1, diff_2);
  switch(diff_1){
  case 1:
    switch(diff_2){
    case 0:
      dir = NW;
      break;
    case 1:
      dir = NE;
      break;
    default:
      dir=ERR;
      break;
    }
    break;
  case 0:
    switch(diff_2){
    case -1:
      dir =W;
      break;
    case 1:
      dir= E;
      break;
    default:
      dir = ERR;
      break;
    }
    break;
  case -1:
    switch(diff_2){
    case -1:
      dir= SW;
      break;
    case 0:
      dir= SE;
      break;
    default:
      dir = ERR;
      break;
    }
    break;
  default:
    dir = ERR;
    break;
  }
  return dir;

}


int valide_cmd(char * cmd){

  int res=0; //0 en cas reussi, 1 en case echoue
  int len = strlen(cmd);
  len+=1;
  printf("len cmd = %d\n cmd = %s\n", len,cmd);
  switch(len){
  case 6:
  case 7:
  case 9:
  case 10:
    
    if(verifie_cmd(cmd, len)==0){
      fprintf(stdout,"commande est syntaxiquement valide!\n");
      
      int dir = dir_mvt(cmd);
      if(dir == ERR){
	fprintf(stderr,"mouvement pas possible!\n");
      }
      else{
	fprintf(stdout, "command et dir sont valides.\n");
	break;
      }
    }
  default:
    printf("mauvaise entree de la cmd: %s Reessayez:\n", cmd);
    res = 1;
    return res;
  }
  
  return res;
}

cercle_t*  recupere_cercle(char *cmd, jeux_t jeux){
  cercle_t c;
  int len = strlen(cmd);
  len+=1;
  cercle_t* cercles = malloc(sizeof(cercle_t) * 3);
  char * nom;
  switch(len){
  case 6:
  case 7:
    printf("entre recupere cercle\n");
    c = malloc(sizeof(struct cercle_s));
    nom =malloc(sizeof(char) * 3);
    nom = strncpy(nom, cmd, 2);
    printf("nom est : %s\n", nom);
    c = nom_to_bille(nom, jeux);
    afficheCercle(c);
    cercles[0] = c;
    return cercles;
    break;
  case 9:
  case 10:
    ////....//
    break;
  default:
    fprintf(stderr, "taille inconnue.\n");
  }
  return cercles;
}

/* int main(int argc, char * argv[]){ */
  
/*   char *cmd =malloc(TAILLE * sizeof(char)); */
/*   while(1){ */
/*     cmd = fgets(cmd, TAILLE,stdin); */
/*     int len =strlen(cmd); */
  
/*     switch(len){ */
/*     case 6: */
/*     case 7: */
/*     case 9: */
/*     case 10: */
      
/*       if(verifie_cmd(cmd, len)==0){ */
/* 	printf("commande est valide!\n"); */
/* 	int dir = dir_mvt(cmd, len); */
/* 	if(dir == ERR){ */
/* 	  printf("mouvement pas possible!\n"); */

/* 	} */
/* 	else{ */
/* 	  break; */
/* 	} */
/*       } */
/*     default: */
/* 	printf("mauvaise entree de la cmd: %s Reessayez:\n", cmd); */
/*     } */
   

/*   }} */
  

 

  

  
