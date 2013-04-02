#include <stdio.h>
#include "def.h"


int main(int argc, char ** argv){
  //cercle tab[9][9] = malloc((sizeof(*cercle)) * 81);
  return 0;
}



void initTableau(cercle[9][9] tab){
  int j;
 for(j=0;j<5;j++)
  tab[0][0]= {1,'B' };
 for(j=5;j<9;j++)
   tab[0][j]=NULL;

 for(j=0;j<6;j++)
    tab[1][0]= {1,'B' };
 for(j=6;j<9;j++)
   tab[1][j]=NULL;

 for(j=2;j<4;j++)
    tab[2][0]= {1,'B' };
 tab[2][0]= {0,'B' };
 tab[2][1]= {0,'B' };
 tab[2][5]= {0,'B' };
 tab[2][6]= {0,'B' };

 for(j=0;j<7;j++)
   tab[3][j]={0,'B'};
for(j=7;j<9;j++)
 tab[3][j]={0,'B'};

for(j=0;j<9;j++)
   tab[4][j]={0,'B'};

for(j=0;j<8;j++)
   tab[5][j]={0,'B'};
 tab[5][8]=NULL;
 

for(j=2;j<4;j++)
    tab[6][0]= {1,'N' };
 tab[6][0]= {0,'N' };
 tab[6][1]= {0,'N' };
 tab[6][5]= {0,'N' };
 tab[6][6]= {0,'N' };

for(j=0;j<6;j++)
    tab[7][0]= {1,'N' };
 for(j=6;j<9;j++)
   tab[7][j]=NULL;
   
 for(j=0;j<5;j++)
  tab[0][0]= {1,'N' };
 for(j=5;j<9;j++)
    tab[0][j]=NULL;
}

 

  


