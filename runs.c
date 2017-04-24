#include "runs.h"

double runs(int n, uint32_t *alea) {
  int i, j;
  uint32_t bit, word;	
  double pi = 0.;
  for(i = 0; i < n/32; i++){
    word = alea[i];
    for(j = 0; j < 32; j++) {
      bit = word << (31-j);
      bit = bit >> 31;
      pi += bit;
    }
  }
  pi = pi/n;
  if(fabs(pi-0.5) >= (2./sqrt(n))) {
    return 0.;
  }
  uint32_t last_bit = alea[0] << 31;
  last_bit = last_bit >> 31;     // A la 1ere ité, last_bit va se comparer à lui
  int stat = 1;                  // meme mais pas grave ça change rien au res
  for(i = 0; i < n/32; i++){
    word = alea[i];
    for(j = 0; j < 32; j++) {
      bit = word << (31-j);
      bit = bit >> 31;
      if(bit != last_bit)
	stat++;
      last_bit = bit;
    }
  }
  double p = erfc(abs(stat-2*n*pi*(1-pi)) / (2*sqrt(2*n)*pi*(1-pi)));
  return p;
}


double runsVN(int n, uint16_t *alea) {
  int i, j;
  uint16_t bit, word;	
  double pi = 0.;
  for(i = 0; i < n/13; i++){
    word = alea[i];
    for(j = 0; j < 12; j++) {
      bit = word << (15-j);
      bit = bit >> 15;
      pi += bit;
    }
  }
  pi = pi/n;
  if(fabs(pi-0.5) >= (2./sqrt(n))) {
    return 0.;
  }
  uint16_t last_bit = alea[0] << 31;
  last_bit = last_bit >> 31;
  int stat = 1;
  for(i = 0; i < n/13; i++){
    word = alea[i];
    for(j = 0; j < 13; j++) {
      bit = word << (15-j);
      bit = bit >> 15;
      if(bit != last_bit)
	stat++;
      last_bit = bit;
    }
  }
  double p = erfc(abs(stat-2*13*pi*(1-pi))/(2*sqrt(2*13)*pi*(1-pi)));
  return p;
}
