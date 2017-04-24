#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "von_neumann.h"
#include "mersenne_twister.h"
#include "monobit.h"
#include "runs.h"
#include "lois.h"
#include "lfsr.h"

#define ARRAY_MAX_SIZE 1000


//static int next;

int rdtsc()
{
  // cette fonction suivante cree un warning : c'est normal.
  __asm__ __volatile__("rdtsc");
}

int main()
{
  word16 x; // nombre entre 1000 et 9999 pour Von Neumann
  struct mt19937p mt; // Pour Mersenne-Twister
  int i, j, seed; // Pour Mersenne-Twister


  uint8_t c = 0x03u;
  uint8_t c2 = 0x01u;
  uint16_t alea1[1024];
  uint32_t alea2[1024];
  uint32_t alea3[1024];
  uint32_t l1, l2, l3, l4;


  // Initialisation de srand pour la suite du programme
  srand(rdtsc());  // rand du C (ne pas appeler dans une boucle)
              
  /* *********************************************************** */
  /* ***** Vecteurs de test pour notre implémentation de E0 **** */
  /* *********************************************************** */
  printf("\n ***********  Vecteurs de test E0  ***********\n");
  verif();


  /* *********************************************************** */
  /*                     Test des générateurs                    */
  /* *********************************************************** */

  printf("\n");
  printf("***********  Von Neumann  ***********\n");


  for(j = 1; j < 21; j++) {
    printf("\n ---  Iteration %d  ---\n", j);

    for (i = 0; i < 1024; i++) {

      x = rand()%(9000)+1000; // Entre 1000 et 9999
      // sorties des generateurs	
      alea1[i] = Von_Neumann(&x); // Von Neumann
    }
    printf("monobit : P = %lf\n", frequencyVN(1024*13, alea1));	
    printf("runs : P = %lf\n", runsVN(1024*13, alea1));
  }

  
  printf("\n");
  printf("***********  Mersenne-Twister  ***********\n");

  for(j = 1; j < 21; j++) {
    printf("\n ---  Iteration %d  ---\n", j);

    seed = rand();
    sgenrand(time(NULL)+(seed), &mt); // Mersenne-Twister

    for (i = 0; i < 1024; i++) {
      // sorties des generateurs	
      alea2[i] = genrand(&mt); // Mersenne-Twister
    }
    printf("monobit : P = %lf\n", frequency(1024*32, alea2));
    printf("runs : P = %lf\n", runs(1024*32, alea2));
  }	
    

  printf("\n");
  printf("***********  E0  ***********\n");
  for(j = 1; j < 21; j++) {
    printf("\n ---  Iteration %d  ---\n", j);
    
    for(i = 0; i < 1024; i++){
      
      l1 = time(NULL) + rand(); // Initialisation
      l2 = time(NULL) + rand(); // des
      l3 = time(NULL) + rand(); // LFSR
      l4 = time(NULL) + rand(); // :)

      // sorties des generateurs
      alea3[i] = fsm_return(l1, l2, l3, l4, c, c2, 32);

      c = rand()%4;
      c2= rand()%4;
    }
    printf("monobit : P = %lf\n", frequency(1024*32, alea3));
    printf("runs : P = %lf\n", runs(1024*32, alea3));
  }
  
  printf("------- loi exponentielle | lambda = 2 -------\n");
  
  for (j = 1; j < 1025; j++) {
	 printf("%lf\n", exponentielle(2.));
  }
  
  return 0;
} // Fin du main

