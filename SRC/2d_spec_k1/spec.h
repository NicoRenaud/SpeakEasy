#ifndef spec_h
#define spec_h
void spec_k1_13( float *W1, int nW1, float *W2, int nW2, float *T, int nT, float *E, float *G, float *U, int nTot, int *ind1, int n1, int *ind2, int n2, char *file_out);
void spec_k1_12( float *W1, int nW1, float *W2, int nW2, float *T, int nT, float *E, float *G, float *U, int nTot, int *ind1, int n1, int *ind2, int n2, char *file_out);
void spec_k1_23( float *W1, int nW1, float *W2, int nW2, float *T, int nT, float *E, float *G, float *U, int nTot, int *ind1, int n1, int *ind2, int n2, char *file_out);
void spec_k1_13_broad( float *W1, int nW1, float *W2, int nW2, float *T, int nT, 
		 float *E0, float *G, float *U, int nTot, int *ind1, int n1, int *ind2, int n2, 
		 SYS sys, char *file_out);
#endif