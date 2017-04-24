#include "monobit.h"

double frequency(int n, uint32_t *alea) { // OK
  int i, j;
  double sobs, p;
  int s = 0;
  uint32_t bit;
  uint32_t word;
  for(i = 0; i < 1024; i++){
    word = alea[i];
    for(j = 0; j < 32; j++) {
      bit = word << (31-j);
      bit = bit >> 31;
      s += (2*bit -1);
    }
  }
  sobs = abs(s)/sqrt((double)n);
  p = erfc(sobs/sqrt(2.0));
  return p;
}

double frequencyVN(int n, uint16_t *alea) { // OK
  int i, j;
  double sobs, p;
  int s = 0;
  uint16_t bit;
  uint16_t word;
  for(i = 0; i < 1024; i++){
    word = alea[i];
    for(j = 0; j < 13; j++) { // 13 car 9999 = 13,28 bits max
      bit = word << (15-j);
      bit = bit >> 15;
      s += (2*bit -1);
    }
  }
  sobs = abs(s)/sqrt((double)n);
  p = erfc(sobs/sqrt(2.0));
  return p;
}
