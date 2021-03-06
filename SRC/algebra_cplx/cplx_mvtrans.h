/////////////////////
//   cplx_mvtrans.h
/////////////////////

#ifndef _cplx_mvtrans_h
#define _cplx_mvtrans_h

void transMat(complex float *M_TR, complex float *M_OR, int size);
void mat2vect_cplx(complex float**mat,complex float *vect,int n);
void vect2mat_cplx(complex float *vect,complex float **mat,int n);

#endif

