#include "lois.h"
#include "lfsr.h"


double alea() {
	uint32_t l1, l2, l3, l4;
	uint32_t alea;
	double unif;
	uint8_t c = 0x03u;
	uint8_t c2 = 0x01u;
	l1 = time(NULL) + rand(); // Initialisation
	l2 = time(NULL) + rand(); // des
	l3 = time(NULL) + rand(); // LFSR
	l4 = time(NULL) + rand(); // :)

	alea = fsm_return(l1, l2, l3, l4, c, c2, 32);
	unif = alea/2147483648.; //2^31
	
	return unif;
}

double exponentielle(double lambda) {
	double unif = alea();
	double expo = -log(1-unif)/lambda;
	return expo;
}