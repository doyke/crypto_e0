OBJ = mersenne_twister.o von_neumann.o monobit.o runs.o lois.o lfsr.o

simu: main_debut.c $(OBJ)
	gcc -Wall -std=c99 -pedantic -o simul main_debut.c $(OBJ) -lm

# Ces 2 lignes définissent la méthode de création d'un .o
.SUFFIXES: .o

.c.o:; gcc -Wall -std=c99 -pedantic -c -o $@ -lm $<

mersenne_twister.o: mersenne_twister.h mersenne_twister.c

von_neumann.o: von_neumann.h von_neumann.c

monobit.o: monobit.h monobit.c

runs.o: runs.h runs.c

lois.o: lois.h lois.c

lfsr.o: lfsr.h lfsr.c

clean:
	rm *.o simul

