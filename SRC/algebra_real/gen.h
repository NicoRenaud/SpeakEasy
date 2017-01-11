////////////////////////////
//	GEN.H
////////////////////////////

#ifndef _gen_h
#define _gen_h
void linspace(float *V, float a, float b, int n);
void reinitVect(float *V,int size);
void eye(float *Id, int n);
void diagonal(float *Vs_mat,float *Vs,int nState);
void check_hermitian_real(float *H,int size);
#endif


