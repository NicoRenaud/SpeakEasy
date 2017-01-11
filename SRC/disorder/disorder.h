#include "../defMacro.h"

#ifndef disorder_h
#define disorder_h

void generateE(float *E, float *E0, int nTot, int ireal, float amp, const gsl_rng_type *T, gsl_rng *r);
void initSeeds_fluct(int *SEEDS_FLUCT, int size);

#endif