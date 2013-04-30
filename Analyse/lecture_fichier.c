#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "../def.h"
#include "lecture_fichier.h"
#include "trait_cmd.h"
#include "../Affichage/affichage_plateau.h"

#define NOMBRE_REGLES 14
#define BUF_TAILLE 256
#define NOMBRE_CERCLES 61
#define REGLE_REF "regle_ref"

/*cette classe:
 1) lecture des fichiers de configuration:
  =>config_ex: cercles 
  =>tab_regles: regle
  =>regles: [table de hachage] annuaire des regles !!!!
 2) initialise le plateau 
 3) renvoie le plateau, l'annuaire des regles (to-be decided)2
*/

char * prochain_mot(FILE *f){
  char * buf = malloc(101);
  if(fscanf(f, " %s", buf)){
      return buf;
    }else{
      return NULL;
  }
}
regle_t traduire_direction(char * s, int cas){
  regle_t t = malloc(sizeof(struct regle_s));
  t->cas = cas;
  t->NW = s[0];
  t->NE = s[1];
  t->E = s[2];
  t->SE = s[3];
  t->SW = s[4];
  t->W = s[5];
  return t;
}

int hachage(table_de_hachage_t table, char cle){
  return (cle % table->taille);
}

void insere(table_de_hachage_t table, char cle, regle_t valeur){
  int hache = hachage(table, cle);
  liste_t c = malloc(sizeof(struct liste_s));
  c->cle = cle;
  c->regle = valeur;
  c->suivant = table->tableau[hache];
  table->tableau[hache] = c;
}



table_de_hachage_t construire_tab_hachage(FILE * f){
  char c;
  char * s = malloc(BUF_TAILLE*sizeof(char));
  regle_t regle;
  
  table_de_hachage_t hash = malloc(sizeof(struct table_de_hachage_s));
  liste_t * tableau = malloc(NOMBRE_REGLES * sizeof(struct liste_s));
  hash->taille = NOMBRE_REGLES;
  hash->tableau = tableau;

  
  s=fgets(s, BUF_TAILLE,f);
 
  c = fgetc(f);

  while(c!='\n'){ //premier char qui n'appartient pas a la liste des regles
    char cle = c;
    s = fgets(s,BUF_TAILLE,f);
    regle = traduire_direction(s,(cle -'0'));
    insere(hash, cle, regle);
    c = fgetc(f);
    
  }
  return hash;
}

regle_t trouver_regle(char cle, table_de_hachage_t table){
  liste_t * tableau = malloc(sizeof(struct liste_s) * NOMBRE_REGLES);
  tableau = table->tableau;
  liste_t liste = tableau[hachage(table,cle)];
  regle_t regle = liste->regle;
  /* int i; */
  /* char c='0'; */
  /* liste_t liste; */
  /* regle_t regle; */
  /* for(i=0; i<14; i++){ */
  /*   liste = tableau[hachage(table,c)]; */
  /*   regle = liste->regle; */
    /* printf("le cas est: %d\n", regle->cas); */
    /* printf("%c \n", regle->NW); */
    /* printf("%c \n", regle->NE); */
    /* printf("%c \n", regle->E); */
    /* printf("%c \n", regle->SE); */
    /* printf("%c \n", regle->SW); */
    /* printf("%c \n", regle->W); */
    /* printf("/--------------/"); */
  /*   c++; */
  /* } */
  return regle;
}




void afficheCercle(cercle_t c){
  printf("commence a afficher\n");
  printf("nom: %s\n", c->nom);
  printf("etat: %d\n", c->etat);
  printf("couleur: %c\n", c->couleur);
  printf("regle: %d\n", c->regle->cas);
  printf("/======================/");
}

jeux_t init_plateau(FILE *tab_bille, FILE* tab_regle, FILE* tab_nom, table_de_hachage_t table){
  char * s;
  char c1, c2,c3,c4; //c1 => char depuis tab_bille, char depuis tab_regle, c3 depuis tab_nom

  char joueur_debut;
  int c_blanc, c_noir;
  jeux_t jeux = malloc(sizeof(struct jeux_s));
 
  // cercle_t cercle = malloc (sizeof(struct cercle_s));
  cercle_t cercle;


  cercle_t * plateau = malloc(sizeof(struct cercle_s) * NOMBRE_CERCLES);
  int indice = 0;
  
  s = fgets(s, BUF_TAILLE, tab_bille);
  joueur_debut = s[0];
  c_blanc = s[1]-'0';
  c_noir = s[2]-'0';
  jeux->joueur = joueur_debut;
  jeux->c_blanc = c_blanc;
  jeux->c_noir = c_noir;

  
  liste_nom_t * table_hachage_nom = malloc(sizeof(liste_nom_t)*NOMBRE_CERCLES);
  while((c1=fgetc(tab_bille)) != EOF && (c2=fgetc(tab_regle)) !=EOF && (c3 = fgetc(tab_nom))!=EOF){
   

     if(c1 == '*' || c2 == '0' || c1 == '\n' || c2 == '\n'){
       continue;
    }
     cercle = malloc (sizeof(struct cercle_s));
    if(c1=='.'){
      cercle->etat = 0; 
    }else{
      cercle->etat = 1;
    }
    cercle->couleur =c1;
    cercle->regle = trouver_regle(c2,table);
    cercle->nom = malloc(sizeof(char)*2);
    c4 = fgetc(tab_nom);
    cercle->nom[0]=c3;
    cercle->nom[1]=c4;
    
    int hash = hash_nom(c3,c4,NOMBRE_CERCLES);
    liste_nom_t ele = malloc(sizeof(struct liste_nom_s));
    ele->cle = cercle->nom;
    ele->indice = indice;
    ele->suivant = table_hachage_nom[hash];
    table_hachage_nom[hash] = ele;
    
    
    plateau[indice] = cercle;
 
    //tester + affichage...
    // afficheCercle(cercle);
    //
    indice++;
  }
  c1=fgetc(tab_bille);
  c2=fgetc(tab_regle);
  if(c1 != EOF || c2 != EOF){
    perror("mauvais correspondance entre fichiers de configuration.\n");
    exit(1);
  }
  jeux->hash_nom = table_hachage_nom;
  jeux->plateau = plateau;

  return jeux;
  
}
 
int hash_nom(char c3, char c4, int taille){
  int somme = pow(c3,2) + pow(c4,2);
  return ( somme % taille);
}


cercle_t nom_to_bille(char * nom, jeux_t jeux){
  int indice = jeux->hash_nom[hash_nom(nom[0],nom[1],NOMBRE_CERCLES)]->indice;

  
  return jeux->plateau[indice];
}



int main (int argc, char * argv[]){
  FILE *f1 = fopen(argv[1], "r"); //regle_ref
  int i;
  table_de_hachage_t table = malloc(sizeof(struct table_de_hachage_s));
  
  table = construire_tab_hachage(f1);
  
  regle_t reg = trouver_regle('0',table);

  FILE *tab_bille = fopen(argv[2],"r");
  FILE * tab_regle = fopen(argv[3],"r");
  FILE * tab_nom = fopen(argv[4],"r");


  jeux_t monJeux;
  
  monJeux = init_plateau(tab_bille, tab_regle,tab_nom, table);
  
  affichage_plateau(monJeux);
  
  /* char * testString = "A3"; */
  
  /* int indice = monJeux->hash_nom[hash_nom(testString[0],testString[1],NOMBRE_CERCLES)]->indice; */
  /* afficheCercle(monJeux->plateau[indice]); */


  //**=======trait cmd + compute =======**//
  char * cmd = malloc(200* sizeof(char));
  cmd  = argv[5];
  int * resultat = malloc(sizeof(int) * 6);  
  if(valide_cmd(cmd)==0){
    cercle_t * cercles =  recupere_cercle(cmd, monJeux);

    int dir = dir_mvt(cmd);
    resultat = verifie_coup(resultat,cercles,dir, monJeux);
    resultat[0] = 0;
    resultat[1] = 0;
    //resultat[4] if ==1 , error code recommence ???
    resultat[5] = 0;
    

  }


  return 0;

}




