/*
 * auxillary.c
 *
 *  Created on: Oct 14, 2013
 *      Author: Qiong Cai and Junying Chen
 */

#include "main.h"

/************ AUXILLARY *************/
int modulo(int a, int m){

	if(m < 0) return modulo(-a, -m);

	int rem = a%m;

	if(rem < 0){
		rem+=m;
	}

	return rem;
}

void lock(int i, bool *locks) {
	bool locked;
        for (locked = false; locked == false; /*NOP*/) {
                #pragma omp critical(LockRegion)
                {
                        locked = !locks[i-1] && !locks[i] && !locks[i+1];
                        if (locked) {
                                locks[i-1] = true; locks[i] = true; locks[i+1] = true;
                        }
                }
        }
}

void unlock(int i, bool *locks) {
        #pragma omp critical(LockRegion)
        {
                locks[i-1] = false; locks[i] = false; locks[i+1] = false;
        }
}

unsigned rand_ud(){

	unsigned short lfsr = 0xACE1u;
	unsigned bit;

	bit = ((lfsr >> 0)^(lfsr >> 2)^(lfsr >> 3)^(lfsr >> 5)) & 1;
	return lfsr = (lfsr >> 1) | (bit << 15);
}
