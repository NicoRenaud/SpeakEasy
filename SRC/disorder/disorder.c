#include "../defMacro.h"

////////////////////////////////////////////////////////////////////////
//	      modifes the value of E
////////////////////////////////////////////////////////////////////////
void generateE(float *ETOT, float *E0, int nTot, int ireal, float amp, const gsl_rng_type *T,gsl_rng *r)
{
  
  
  int i,j,k = 0;
  double fluct;
  double amp_dbl = (double) amp;
  int shift = ireal*nTot;

  for(i=0;i<nTot;i++)
  {
     fluct = gsl_ran_gaussian(r,amp_dbl);
     printf("%lf ",fluct);
     ETOT[shift+i] = E0[i] + (float) fluct;
  }

}


////////////////////////////////////////////////////////////////////////
//	      initalize the seeds for the fluctuation
////////////////////////////////////////////////////////////////////////
void initSeeds_fluct(int *SEEDS_FLUCT, int size)
{
  
  // variable
   int i;
  
  // initialise seed 
  srand(time(NULL));
  
  for(i=0;i<size;i++)
    SEEDS_FLUCT[i] = rand();
 
}
