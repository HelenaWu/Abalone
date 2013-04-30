char * prochain_mot(FILE *f);
regle_t traduire_direction(char * s, int cas);
int hachage(table_de_hachage_t table, char cle);
void insere(table_de_hachage_t table, char cle, regle_t valeur);
table_de_hachage_t construire_tab_hachage(FILE * f);
int hash_nom(char c3, char c4, int taille);
cercle_t nom_to_bille(char * nom, jeux_t jeux);
