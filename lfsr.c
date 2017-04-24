#include "lfsr.h"

int power(int a, int b) {
  if(b == 1) return a;
  return a * power(a, b-1);
}

uint32_t lfsr1(uint32_t start_state) {
  
  uint32_t lfsr = start_state;
  uint32_t bit, bit25, bit20, bit12, bit8;  
  bit = bit25 = bit20 = bit12 = bit8 = 0;

  /*  x^25 + x^20 + x^12 + x^8 + 1    LFSR1 */
  bit25 = lfsr << 7;
  bit25 = bit25 >> 31;

  bit20 = lfsr << 12;
  bit20 = bit20 >> 31;

  bit12 = lfsr << 20;
  bit12 = bit12 >> 31;

  bit8 = lfsr << 24;
  bit8 = bit8 >> 31;

  bit  = bit25 ^ bit20 ^ bit12 ^ bit8 ;
  // Pour supprimer les 8 bits de poids fort inutiles
  lfsr = lfsr << 8;
  lfsr = lfsr >> 8;

  lfsr =  (lfsr << 1) | bit;

  return lfsr;
}

uint32_t lfsr2(uint32_t start_state) {

  uint32_t lfsr = start_state;
  uint32_t bit, bit31, bit24, bit16, bit12;  
  bit = bit31 = bit24 = bit16 = bit12 = 0;

  /* x^31 + x^24 + x^16 + x^12 + 1    LFSR2 */

  bit31 = lfsr << 1;
  bit31 = bit31 >> 31;

  bit24 = lfsr << 8;
  bit24 = bit24 >> 31;

  bit16 = lfsr << 16;
  bit16 = bit16 >> 31;

  bit12 = lfsr << 20;
  bit12 = bit12 >> 31;

  bit  = bit31 ^ bit24 ^ bit16 ^ bit12 ;
  // Pour supprimer les 2 bits de poids fort inutiles
  lfsr = lfsr << 2;
  lfsr = lfsr >> 2;

  lfsr =  (lfsr << 1) | bit;

  return lfsr;
}

uint64_t lfsr3(uint64_t start_state) {
  
  uint64_t lfsr = start_state;
  uint64_t bit, bit33, bit28, bit24, bit4;  
  bit = bit33 = bit28 = bit24 = bit4 = 0;

  /* taps: 33 28 24 4; feedback polynomial: x^33 + x^28 + x^24 + x^4 + 1    LFSR4 */
  
  bit33 = lfsr << 31;
  bit33 = bit33 >> 63;

  bit28 = lfsr << 36;
  bit28 = bit28 >> 63;

  bit24 = lfsr << 40;
  bit24 = bit24 >> 63;

  bit4 = lfsr << 60;
  bit4 = bit4 >> 63;

  bit  = bit33 ^ bit28 ^ bit24 ^ bit4 ;
  // Pour supprimer les 32 bits de poids fort inutiles
  lfsr = lfsr << 32;
  lfsr = lfsr >> 32;

  lfsr =  (lfsr << 1) | bit;

  return lfsr;
}

uint64_t lfsr4(uint64_t start_state) {
  
  uint64_t lfsr = start_state;
  uint64_t bit, bit39, bit36, bit28, bit4;  

  bit = bit39 = bit36 = bit28 = bit4 = 0;

  bit39 = lfsr << 25;
  bit39 = bit39 >> 63;

  bit36 = lfsr << 28;
  bit36 = bit36 >> 63;

  bit28 = lfsr << 36;
  bit28 = bit28 >> 63;

  bit4 = lfsr << 60;
  bit4 = bit4 >> 63;

  bit  = bit39 ^ bit36 ^ bit28 ^ bit4 ;
  // Pour supprimer les 26 bits de poids fort inutiles
  lfsr = lfsr << 26;
  lfsr = lfsr >> 26;

  lfsr =  (lfsr << 1) | bit;

  return lfsr;
}

void test_fsm(uint32_t l1, uint32_t l2, uint64_t l3, uint64_t l4, uint8_t c, uint8_t c2) {
  int i = 0;
  uint8_t new_c0, s, stmp, tmp1;
  uint32_t y, bit1, bit2;
  uint64_t bit3, bit4;
  bit1 = 0;
  bit2 = 1;
  bit3 = bit4 = 0;
  int t = 240;
  printf("\n");
  new_c0 = 0x02u;

  y = bit1 + bit2 + bit3 + bit4 + c;
  printf("%d %X %X %lX %lX %u %u %lu %lu %u %u %u %u \n",
	 t+i, l1, l2, l3, l4,bit1, bit2, bit3, bit4, y%2, new_c0, c, c2);

  for(i = 1; i < 35; i++) {

    // pour lfsr1 : bit 23
    bit1 = l1 << 9;
    bit1 = bit1 >> 31;
    // pour lfsr2 : bit 23
    bit2 = l2 << 9;
    bit2 = bit2 >> 31;

    // pour lfsr3 : bit 31
    bit3 = l3 << 33;
    bit3 = bit3 >> 63;
  
    // pour lfsr4 : bit 31
    bit4 = l4 << 33;
    bit4 = bit4 >> 63;

    // maj des lfsr
    l1 = lfsr1(l1);
    l2 = lfsr2(l2);
    l3 = lfsr3(l3);
    l4 = lfsr4(l4);

    c2 = c;
    c = new_c0;

    // calcul de y
    y = bit1 + bit2 + bit3 + bit4 + c;

    // calcul de s(t+1)
    s = y/2;

    //on cacule le bit c1
    stmp = s << 6;
    stmp = stmp >> 7;
    tmp1 = c << 6;
    tmp1 = tmp1 >> 7;
    new_c0 = 2*(stmp ^ tmp1 ^ (c2%2));
    //on ajoute le bit c0 c0
    tmp1 = c2 << 6;
    tmp1 = tmp1 >> 7;
    new_c0 = new_c0 + (s%2 ^ (c%2) ^ tmp1 ^ (c2%2));
    
    printf("%d %X %X %lX %lX %u %u %lu %lu %u %u %u %u \n",
	   t+i, l1, l2, l3, l4,bit1, bit2, bit3, bit4, y%2, new_c0, c, c2);
  }
}

uint32_t fsm_return(uint32_t l1, uint32_t l2, uint64_t l3, uint64_t l4, uint8_t c, uint8_t c2, int nb_occ) {
  int i = 0;
  uint8_t new_c0, s, stmp, tmp1;
  uint32_t y, bit1, bit2;
  uint64_t bit3, bit4;

  uint32_t alea = 0;

  bit1 = 0;
  bit2 = 1;
  bit3 = bit4 = 0;
  new_c0 = 0x02u;

  y = bit1 + bit2 + bit3 + bit4 + c;

  alea = alea + y%2;

  for(i = 1; i < nb_occ; i++) {

    // pour lfsr1 : bit 23
    bit1 = l1 << 9;
    bit1 = bit1 >> 31;
    // pour lfsr2 : bit 23
    bit2 = l2 << 9;
    bit2 = bit2 >> 31;

    // pour lfsr3 : bit 31
    bit3 = l3 << 33;
    bit3 = bit3 >> 63;
  
    // pour lfsr4 : bit 37
    bit4 = l4 << 33;
    bit4 = bit4 >> 63;

    // maj des lfsr
    l1 = lfsr1(l1);
    l2 = lfsr2(l2);
    l3 = lfsr3(l3);
    l4 = lfsr4(l4);

    c2 = c;
    c = new_c0;

    // calcul de y
    y = bit1 + bit2 + bit3 + bit4 + c;

    // calcul de s(t+1)
    s = y/2;

    //on cacule le bit c1
    stmp = s << 6;
    stmp = stmp >> 7;
    tmp1 = c << 6;
    tmp1 = tmp1 >> 7;
    new_c0 = 2*(stmp ^ tmp1 ^ (c2%2));
    //on ajoute le bit c0 c0
    tmp1 = c2 << 6;
    tmp1 = tmp1 >> 7;
    new_c0 = new_c0 + (s%2 ^ (c%2) ^ tmp1 ^ (c2%2));

    alea = alea << 1;
    alea = alea + y%2;
  }
  return alea;
}

void verif() {
  uint32_t l1 = 0x004B583Du;
  uint32_t l2 = 0x208E1EC1u;
  uint64_t l3 =  0x0000000063C142F0u;
  uint64_t l4 =  0x0000000F7A2A42BBu;
  uint8_t c = 0x03u;
  uint8_t c2 = 0x01u;

  test_fsm(l1, l2, l3, l4, c, c2);

}


void calc() {
  uint8_t c = 0x03u; /* entre 0 et 3 */
  uint8_t c2 = 0x01u; /* entre 0 et 3 */
  int i;
  uint32_t alea;
  for(i = 0; i < 1024; i++){
    alea = fsm_return(time(NULL) + rand(), time(NULL) + rand(), time(NULL) + rand(), time(NULL) + rand(), c, c2, 32);
    printf("\n%u", alea);
  }
}




