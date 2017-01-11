#include "../defMacro.h"




/////////////////////////////////////////////////////////
//  Transforme une matrice float en matrice complex    //
/////////////////////////////////////////////////////////
void reinitVect_cplx(complex float *V,int size)
{
    int i;
    for(i=0;i<size;i++)
      V[i] = 0.+I*0;
}

/////////////////////////////////////////////////////////
//  Transforme une matrice float en matrice complex    //
/////////////////////////////////////////////////////////
void dbl2cplx(complex float *CPLX, float *DBL, int n)
{
    int i;
    for(i=0;i<n;i++)
    {
	CPLX[i] = (complex float) DBL[i];
    }
}


/////////////////////////////////////////////////////////
//  	    normalize a complex matrix    	       //
/////////////////////////////////////////////////////////
void normDM(complex float *RHO, int size)
{
    int i;
    complex float tr;
    
    tr = 0.+I*0.;
    
    // comppute the trace
    for(i=0;i<size;i++)
      tr += RHO[i*(size+1)];
    
//     printf("NORM = %f+i%f\n",crealf(tr),cimagf(tr));
    
    // normalise DM
    for(i=0;i<size*size;i++)
      RHO[i] = RHO[i]/tr; 
  
}
