//////////////////////////
// header
/////////////////////////

#ifndef define_matrices_h
#define define_matrices_h

void compute_energies(float *E, float *H, int nState);
void define_relax_from_h(float *R, float *H, float gama_0, int nState, float temp);
void define_dephas(float *R, float *H, float gama_0, int nState, float sigma,float temp);
void define_grd2sgl_dipole(float *D,float * H, int nState, int grd2sgl_dipole, int grd2sgl_freq, int grd2sgl_width);
void define_sgl2dbl_dipole_gsn(float *D,float *E, int *ind1, int n1, int *ind2, int n2, float sgl2dbl_dipole, float sgl2dbl_freq, float sgl2dbl_width);
#endif