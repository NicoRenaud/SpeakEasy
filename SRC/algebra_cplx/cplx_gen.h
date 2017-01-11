/////////////////////
//   cplx_gen.h
/////////////////////

#ifndef _cplx_gen_h
#define _cplx_gen_h

void reinitVect_cplx(complex float *V,int size);
void dbl2cplx(complex float *CPLX, float *DBL, int n);
void normDM(complex float *RHO, int size);

#endif
