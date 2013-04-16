#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int main(int argc, char * argv[]){
  FILE * f = fopen(argv[1], "r+");
  char* sa = malloc(1000 * sizeof(char));
  sa = fgets(sa,1000, f);
  char c = fgetc(f);
  while(c!=EOF){
    if(c==''){
      c=''
      

  printf("%s",sa);


}
