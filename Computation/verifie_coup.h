void  verifie_coup(int * resultat, cercle_t * cercles, int direction, jeux_t jeux, char joueur_couranty);
int * recurse_verifie(int * resultat, cercle_t cercle, int  direction, jeux_t jeux);
char  dir_int_to_char(regle_t regle, int direction);
int valide_couleur(int couleur_etat, cercle_t c);
char * nouvelle_position(char* nom_courant, int direction);
