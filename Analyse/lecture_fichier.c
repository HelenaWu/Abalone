#include<stdio.h>
#include<stdlib.h>
#include "../def.h"

#define NOMBRE_REGLES 14
#define BUF_TAILLE 256
/*cette classe:
 1) lecture des fichiers de configuration:
  =>config_ex: cercles 
  =>tab_regles: regle
  =>regles: [table de hachage] annuaire des regles 
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

table_de_hachage_t construire_tab_hachage(FILE * f){
  char c;
  char * s = malloc(BUF_TAILLE*sizeof(char));
  regle_t regle;
  
  table_de_hachage_t hash = malloc(sizeof(struct table_de_hachage_s));
  liste_t * tableau = malloc(NOMBRE_REGLES * sizeof(struct liste_s));
  hash->taille = NOMBRE_REGLES;
  hash->tableau = tableau;

  while((c=fgetc(f))!='0'){
    c = fgetc(f); //saute la premiere ligne
  }//remplcae avec fgets
  /** test si fgets inclu \n**/

  while(c!=EOF){
    char cle = c;
    s = fgets(s,BUF_TAILLE,f);
    regle = traduire_direction(s, atoi(cle));
    insere(hash, cle, regle);
    c = fgetc(f);
  }
  return hash;
}

regle_t traduire_direction(char * s, int cas){
  regle_t t = malloc(sizeof(struct regle_s));
  t.cas = cas;
  t.NW = s[0];
  t.NE = s[1];
  t.E = s[2];
  t.SE = s[3];
  t.SW = s[4];
  t.W = s[5];
  return t;
}

int hachage(table_de_hachage_t table, char cle){
  return (cle % table->taille);
}
void insere(table_de_hachage_t table, char cle, regle_t valeur){
  int hache = hachage(table, cle);
  Liste_t c = malloc(sizeof(struct liste_s));
  c->cle = cle;
  c->regle = valeur;
  c->suivant = table->tableau[hache];
  table->tableau[hache] = c;
}



jeux  parse(char* nom_fichier){
  /* FILE *f = fopen(nom_fichier, "r+"); */
  /* char * joueur = prochain_mot(f); */
  /* if(strcmp(joueur,"N")==1 || strcmp(joueur, "B")==1){ */
  /*   printf("retaper nom_joeur"); */
  /*   Exit(1); */
  /* } */
  /* int c_blanc = prochain_mot(f); */
  /* int c_noir = prochain_mot(f); */
  
 

}


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




