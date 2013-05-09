#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>
#include<math.h>
#include "def.h"
#include<string.h>
#include "./Analyse/lecture_fichier.h"
#include "./Analyse/trait_cmd.h"
#include "Affichage/affichage_plateau.h"

#define NOMBRE_REGLES 14
#define BUF_TAILLE 256
#define NOMBRE_CERCLES 61
//#define REGLE_REF "regle_ref"

char * concat_char(char* bille_noms, jeux_t jeux){
  char * res = malloc(50);
  char * res_2 = malloc(50);
  char* nom_courant = malloc(3);
  int i=0;
  char c_proc;
  while(*(bille_noms)!='\0'){
    if(*bille_noms=='*'){
      c_proc = '*';
      if(!*(bille_noms) == '\0'){
	bille_noms+=1;
      }
    }
    else{
      //  printf("bille_nom[i] = %c, [i+1] = %c, i = %d\n", bille_noms[i],bille_noms[i+1],i);
      nom_courant = strncpy(nom_courant,bille_noms,2);
      c_proc = nc(jeux,nom_courant);
      if(!*(bille_noms) == '\0'){
	bille_noms+=2;
      }
    }
    char * str_proc = malloc(10);
    str_proc = &c_proc;
  
    res =  strncat(res,str_proc,1);
     
  }
 
  return res;
}

void ligne_to_fich(char * ligne,FILE * fich_sv, jeux_t jeux){
  char * res = malloc(20);
  res = concat_char(ligne, jeux);
 
  char * ptr = res;
  while(*ptr!='\0'){
 
    fputc(*ptr,fich_sv);
    
    ptr++;
  }
}

void sauvegarde(jeux_t jeux,char mode){
  //mode 'm' => muet, 'i'=> interactif
  FILE * fich_sv = NULL;
  
  if(mode == 'i'){
  printf("Quel nom voulez-vous donner a votre sauvegarde?[taille max: 100 char]\n");
  char * nom_sv = malloc(104);
  nom_sv = fgets(nom_sv, 100,stdin);
  
  int len_fich = strlen(nom_sv);
  char * nom_sv_2 = malloc(104);
  strncpy(nom_sv_2,nom_sv,(len_fich-1));

  nom_sv = strcat(nom_sv_2,".sv");
  fich_sv = fopen(nom_sv,"w");
  }
  if(mode == 'm'){
    fich_sv = fopen("redo.sv","w");
  }

  fputc(jeux->joueur,fich_sv);
  fputc((jeux->c_blanc+'0'),fich_sv);
  fputc((jeux->c_noir+'0'),fich_sv);
  fputc('\n',fich_sv);
  
 
  char * tab[] = {"****I5I6I7I8I9","***H4H5H6H7H8H9","**G3G4G5G6G7G8G9","*F2F3F4F5F6F7F8F9","E1E2E3E4E5E6E7E8E9","D1D2D3D4D5D6D7D8*","C1C2C3C4C5C6C7**","B1B2B3B4B5B6***","A1A2A3A4A5****"};
 
  int k;
  for(k=0; k<9;k++){
    ligne_to_fich(tab[k],fich_sv,jeux);
    if(k!=8){
    fputc('\n',fich_sv);
    }
  }



  fclose(fich_sv);
}

 
int main (int argc, char * argv[]){



  FILE *f1 = fopen("regle_ref", "r"); //regle_ref
  int i;
  table_de_hachage_t table;// = malloc(sizeof(struct table_de_hachage_s));
  
  table = construire_tab_hachage(f1);
  


  FILE * tab_bille = fopen("tab_bille","r");


  FILE * tab_regle = fopen("tab_regle","r");
  FILE * tab_nom = fopen("tab_nom","r");

  jeux_t monJeux;
  


  printf("Bienvenue, joueur!\nVoulez-vous jouer a partir de la position: initiale [init]  \nou a partir d'une sauvegarde? [save] \n");
  char * etat_init = malloc(200);
  etat_init= fgets(etat_init, 10, stdin);
  if(strcmp(etat_init,"save\n")==0){
    
    printf("Voulez-vous lire depuis quelle fichiers?\n");
    system("find *.sv > nom_fich_sv");
    FILE * nom_fich_sv = fopen("nom_fich_sv","r");
    char * nom_sv = malloc(50);
    
    printf("Tous les sauvegardes: \n");
    while((fgets(nom_sv,50,nom_fich_sv))!=NULL){
      if(strcmp(nom_sv,"redo.sv\n")!=0){
	printf("%s",nom_sv);
      }
    }
    fclose(nom_fich_sv);
    free(nom_sv);
    
    char * fich_init_1 = malloc(200);
    fich_init_1= fgets(fich_init_1, 200, stdin);
    int len_fich = strlen(fich_init_1)-1;
    char * fich_init_2  = malloc(200);
    strncpy(fich_init_2,fich_init_1,len_fich);
    
    tab_bille = fopen(fich_init_2,"r");

    free(fich_init_1);
    free(fich_init_2);
  }


  monJeux = init_plateau(tab_bille, tab_regle,tab_nom, table);
 
  

  affichage_plateau(monJeux);
  

  //**=======trait cmd + compute =======**//
  char * cmd = malloc(10* sizeof(char));
  int* resultat = malloc(sizeof(int*) * 6);
  /*---initialise resultat---*/
  

  for(i=0; i<6; i++){
    resultat[i] = 0;
  }
 
  char joueur_courant = monJeux->joueur;

  int compte = 0;
  char* mode = malloc(20);
  FILE * source =stdin;
   
  char * nom_fichier_1 = malloc(200);
  char * nom_fichier_2 = malloc(200);
            
  while(1){
    printf("Vous choissisez quel mode:\nMode jeux [jeux]\nMode test [test] \n");
    mode = fgets(mode,20,stdin);
		
    if(strcmp(mode,"test\n")==0){
   
      fprintf(stdout,"Quel fichier voulez-vous charger?\n"); 

      system("find *.tst > nom_fich_tst");
      FILE * nom_fich_tst = fopen("nom_fich_tst","r");
      char * nom_tst = malloc(50);
    
      printf("Tous les fichiers test: \n");
      while((fgets(nom_tst,50,nom_fich_tst))!=NULL){
	printf("%s\n",nom_tst);
      }
      fclose(nom_fich_tst);
      free(nom_tst);
	  
      nom_fichier_1= fgets(nom_fichier_1,200,stdin);
	  
      // printf("nom_fichie est :%s" ,nom_fichier_1); 
	 
      int len_nom = strlen(nom_fichier_1)-1;
      strncpy(nom_fichier_2,nom_fichier_1,len_nom);
	    
      //printf("nom_2 est: %s",nom_fichier_2);
	    
      source = fopen(nom_fichier_2,"r"); 
	  
      break;
	  
    }  
    if(strcmp(mode,"jeux\n")==0){
      source = stdin;
	  
      if(monJeux->joueur=='X'){
	printf("Quel joueur vous etes? Blanc[B]: Noir[N]");
	char * type_joueur  = malloc(3);
	type_joueur = fgets(type_joueur, 3,stdin);

	   
	if(strcmp(type_joueur,"B\n")==0){
	  joueur_courant = 'B';
	     
	  break;
	}
	if(strcmp(type_joueur,"N\n")==0){
	  joueur_courant = 'N';
	  break;
	}
	else{
	  printf("type joueur inconnu, reentrez.\n");
	  continue;
	}
      }
      else{
	break;
      }
	  
    }
	
	
	
    else{
      printf("mode inconnue. Reentrez.\n");
    }
  

  }
  monJeux->joueur = joueur_courant;
  
  
  while(resultat[2]!=6 || resultat[3] != 6){
 
 
    
    if(strcmp(mode,"jeux\n")==0){
      printf("entrez votre commande joueur %c :\n'jouer un coup';'sauvegarder jeux courant [save]';\n'Quitter[quit]'; 'Rejoue le dernier coup[redo]'\n",joueur_courant);
    }
    cmd  = fgets(cmd, 10, source);

        
    
    if(strcmp(cmd,"save\n")==0){
      sauvegarde(monJeux,'i');
     
    }
    if(strcmp(cmd,"quit\n")==0){
      exit(0);
    }
    if(strcmp(cmd,"redo\n")==0){
      
      FILE * redo = fopen("redo.sv","r");
      if(redo == NULL){
	printf("redo est null.\n");
      }
      tab_regle = fopen("tab_regle","r");
      tab_nom = fopen("tab_nom","r");
     
      monJeux = init_plateau(redo,tab_regle,tab_nom,table);
      
      affichage_plateau(monJeux);
      
    }
       
    else{
      printf("cmd est: %s\n", cmd);
      if(valide_cmd(cmd)==0){
	cercle_t * cercles =  recupere_cercle(cmd, monJeux);
      
	int dir = dir_mvt(cmd);
	sauvegarde(monJeux,'m');  

	verifie_coup(resultat,cercles,dir, monJeux, joueur_courant);
						
	monJeux->joueur = joueur_courant;
	monJeux->c_blanc = resultat[3];
	monJeux->c_noir = resultat[2];
	joueur_courant = (joueur_courant=='B')? 'N' :'B';

	affichage_plateau(monJeux);
   
	resultat[0] = 0;
	resultat[1] = 0;

	if(resultat[4] ==1){
	  fprintf(stderr, "il y avait un probleme quelque part. Reessayez\n");
	
	}
	resultat[4] = 0;
	resultat[5] = 0;
    
      }else{
	//si commande n'est pas bon.
      }
    }
  }
    
  return 0;
  
}




  


