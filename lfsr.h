#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <math.h>

uint32_t lfsr1(uint32_t start_state);

uint32_t lfsr2(uint32_t start_state);

uint64_t lfsr3(uint64_t start_state);

uint64_t lfsr4(uint64_t start_state);

void test_fsm(uint32_t l1, uint32_t l2, uint64_t l3, uint64_t l4, uint8_t c, uint8_t c2);

uint32_t fsm_return(uint32_t l1, uint32_t l2, uint64_t l3, uint64_t l4, uint8_t c, uint8_t c2, int nb_occ);

void verif();

void calc();

int power(int a, int b);
