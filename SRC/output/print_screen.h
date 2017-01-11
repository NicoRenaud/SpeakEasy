//////////////////////
// print_screen
//////////////////////

#ifndef _print_screen_h
#define _print_screen_h

void print_header(SYS sys);
void print_end(char *OUT_DIR, char *OUT_PATH, int nT) ;
void print_mat(float* MAT,int n1,int n2, char *name);
void print_mat_file(float* MAT,int n1,int n2, char *name, char *file_name);
void print_vect_int(int  *VECT, int n,char *name);
void print_sum_mat(float *MAT,int n1,char *name);
void print_mat_C(complex float *MAT, int n1, int n2, char *name);
void print_vect_C(complex float *vect, int n1, char *name);
void print_info(int nK, int nReal, int time, int nbSwap, float nrj);
void print_vect(float *VECT, int n,char *name);

#endif