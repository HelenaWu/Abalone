#Variables
CC = gcc
CFLAGS = -Wall
PROGRAM = main
OBJECTS = main.o  ./Computation/verifie_coup.o ./Computation/mise_a_jour.o ./Analyse/trait_cmd.o ./Analyse/lecture_fichier.o ./Affichage/affichage_plateau.o
SOURCES = $(patsubst %.o, %.c,$(OBJECTS))
SUBDIRS = Analyse Computation Affichage 

#Dir
include ./Analyse/Makefile
.PHONY: clean 

all: $(PROGRAM)
$(PROGRAM): $(OBJECTS)
	$(CC) -o $@ $+

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

main.o: def.h ./Analyse/lecture_fichier.h ./Analyse/trait_cmd.h ./Affichage/affichage_plateau.h 
verifie_coup.o: mise_a_jour.h def.h verifi_coup.h lecture_fichier.h
lecture_fichier.o: def.h lecture_fichier.h trait_cmd.h affichage_plateau.h
trait_cmd.o: def.h lecture_fichier.h trait_cmd.h
mise_a_jour.o: mise_a_jour.h
affichage_plateau.o: affichage_plateau.h lecture_fichier.h



clean:	
	rm -f main *.o *~ \#*
	 for dir in $(SUBDIRS); do \
	 	 $(MAKE) clean -C $$dir; \
	 done
