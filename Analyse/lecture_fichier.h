char * prochain_mot(FILE *f);
regle_t traduire_direction(char * s, int cas);
int hachage(table_de_hachage_t table, char cle);
void insere(table_de_hachage_t table, char cle, regle_t valeur);
table_de_hachage_t construire_tab_hachage(FILE * f);
