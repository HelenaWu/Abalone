#include<stdio.h>
#include<stdlib.h>
#include "../def.h"
#include "lecture_fichier.h"

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
 3) renvoie le plateau, l'annuaire des regles (to-be decided)
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

  while(c!=EOF){
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
  printf("%c \n", regle->SW);
  return regle;
}


jeux_t init_plateau(FILE *tab_bille, FILE* tab_regle, table_de_hachage_t table){
  char * s;
  char c1, c2; //c1 => char depuis tab_bille, char depuis tab_regle

  char joueur_debut;
  int c_Blanc, c_Noir;
  jeux_t jeux = malloc(sizeof(struct jeux_s));
  cercle_t cercle = malloc (sizeof(struct cercle_s));
  cercle_t * plateau = malloc(sizeof(struct cercle_s) * NOMBRE_CERCLES);
  int indice = 0;
  
  s = fgets(s, BUF_TAILLE, tab_bille);
  joueur_debut = s[0];
  c_blanc = s[1]-'0';
  c_noir = s[2]-'0';
  jeux->joueur = joueur_debut;
  jeux->c_blanc = c_blanc;
  jeux->c_noir = c_noir;

  
  while((c1=fgetc(tab_bille)) != EOF && (c2=fgetc(tab_regle)) !=EOF){
    if(c1 == '*' || c2 = '0'){
      continue;
    }
    if(c1=='.'){
      cercle->etat = 0;
    }else{
      cercle->etat = 1;
    }
    cercle->couleur =c1;
    cercle->regle = trouver_regle(c2,table); 
    plateau[indice] = cercle;
    indice++;
  }
  if(c1 == EOF || c2 == EOF){
    perror("mauvais correspondance entre fichiers de configuration.\n");
    Exit(1);
  }
  jeux->plateau = plateau;
  return jeux;
  
}



int main (int argc, char * argv[]){
  FILE *f1 = fopen(argv[1], "r+");
  int i;
  table_de_hachage_t table = malloc(sizeof(struct table_de_hachage_s));
  
  table = construire_tab_hachage(f1);
  
  regle_t reg = trouver_regle('1',table);

  FILE *tab_bille = fopen(argv[2],"r+");
  FILE * tab_regle = fopen(argv[3],"r+");
  

  return 0;

}




