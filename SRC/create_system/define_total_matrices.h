#ifndef def_tot_mat
#define def_tot_mat

void define_total_relaxation(float *G, float *R, int *index1, int *index2, SYS sys);
void define_total_dipole(float *U, float *D, float *D2, int *index1, int n1, int *index2, int n2);

#endif