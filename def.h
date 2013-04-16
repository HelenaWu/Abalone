
#ifndef STRUCT_REGLE
#define STRUCT_REGLE 

typedef struct regle_s{
  int cas; 
  char NW;
  char NE;
  char E;
  char SE;
  char SW;
  char W;
}*regle_t;

#endif

#ifndef STRUCT_CERCLE
#define STRUCT_CERCLE 

typedef struct cercle_s{
  int vide;
  char couleur;
  regle_t regle;
}*cercle_t;

#endif



#ifndef LISTE
#define LISTE
typedef struct liste_s{
  char cle;
  regle_t regle;
  struct list_s *suivant;
}*liste_t;
#endif


#ifndef TABLE_HACHAGE
#define TABLE_HACHAGE
typedef struct table_de_hachage_s{
  int taille;
  liste_t *tableau;
}*table_de_hachage_t;
#endif

#ifndef JEUX
#define JEUX
 typedef struct jeux_s {
    char joueur;
    int c_blanc;
    int c_noir;
    cercle_t * plateau;
 }*jeux_t;
#endif
