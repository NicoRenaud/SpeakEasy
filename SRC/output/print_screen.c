
#include "../defMacro.h"

////////////////////////////////////
// Print the header of the program //
////////////////////////////////////
void print_header(SYS sys) {
 
  printf("\n====  ===============================  ====\n");    
  printf("====                                   ====\n");   
  printf("====  	        Speakeasy	       ====\n"); 
  printf("====                                   ====\n");   
  printf("====  ===============================  ====\n\n");
  
  printf(" == Number of states		\t: %d\n",sys.nState);
  printf(" == System Hamiltonian           \t: %s\n",sys.hmltn_mat);
  printf(" == System Absorption Dipole	\t: %s\n",sys.dipole_mat);
  printf(" == System Relaxation Matrix	\t: %s\n",sys.relax_mat);
  printf(" == Excitation Frequencies	\t: %1.3f to %1.3f (%d points)\n",sys.minW1,sys.maxW1,sys.nW1);
  printf(" == Emission Frequencies	\t: %1.3f to %1.3f (%d points)\n",sys.minW2,sys.maxW2,sys.nW2);
  printf(" == Evolution time (fs)	       \t: %1.3f to %1.3f (%d points)\n",sys.t0/FS2UA,sys.tmax/FS2UA,sys.nDiv);
  printf(" == Inhomogeneous broadening	\t: %1.3f for %d real\n",sys.disorder_amp,sys.disorder_nReal);
  printf(" \n====  ===============================  ====\n");
  
}


////////////////////////////////////
// Print the end of file//
////////////////////////////////////
void print_end(char *OUT_DIR, char *OUT_PATH, int nT) 
{
  int i;
  printf("\n==  ==================================== ==\n");
  printf("==      COMPUTATION DONE WITH SUCCESS	 ==\n");
  printf("==  ==================================== ==\n");
  printf("\n == Output files written in %s	\n\n",OUT_PATH);
//   for(i=0;i<nT;i++)
//     printf("\t-- %s%d.sci\n",OUT_PATH,i+1);
  printf("\n====  ===============================  ====\n");    
  printf("====    Thank you for using            ====\n"); 
  printf("====                       Speakeasy   ====\n");   
  printf("====  ===============================  ====\n\n");
  

  
}



////////////////////////////////////
//      Print a Matrix            //
////////////////////////////////////

void print_mat(float* MAT,int n1,int n2, char *name){
      
     int i,j,k=0;
     printf("\n %s= [\n",name);
     for(i=0;i<n1;i++)
     {
//                       printf("\t\t");
                      for(j=0;j<n2;j++)
                      {
                                       printf("%1.3f ",MAT[k]);
					k++;
                      }
                      printf("\n");
      }  
      printf("\t     ];\n"); 
}


////////////////////////////////////
//      Print a Matrix    in a file        //
////////////////////////////////////

void print_mat_file(float* MAT,int n1,int n2, char *name, char *file_name){
      
     int i,j,k=0;
     FILE *f;
     
     f = fopen(file_name,"w");
     if (!f) {
      printf("couldn't read %s\n", file_name);
      exit(1);
     }
     
     fprintf(f,"\n %s= [\n",name);
     for(i=0;i<n1;i++)
     {
//                       printf("\t\t");
                      for(j=0;j<n2;j++)
                      {
                                       fprintf(f,"%2.6f ",MAT[k]);
					k++;
                      }
                      fprintf(f,"\n");
      }  
      fprintf(f,"\t     ];\n"); 
}

////////////////////////////////////
//      Print a ComplexMatrix       //
////////////////////////////////////
void print_mat_C(complex float *MAT, int n1, int n2, char *name)
{
      
     int i,j,k=0;
     printf("\n %s= [\n",name);
     for(i=0;i<n1;i++)
     {
                      printf("\t");
                      for(j=0;j<n2;j++)
                      {
                                       printf("%1.6f+%%i*%1.6f ",crealf(MAT[k]),cimagf(MAT[k]));
					k++;
                      }
                      printf("\n");
      }  
      printf("\t ];\n"); 
}


////////////////////////////////////
//      Print a Vector            //
///////////////////////////////////
void print_vect(float *VECT, int n,char *name){
     int i;
     printf("\n %s= [ ",name);
     for(i=0;i<n;i++)
                     printf("%2.5g ",VECT[i]);
     printf(" ]\n");
}


void print_vect_int(int  *VECT, int n,char *name){
     int i;
     printf("\n %s= [ ",name);
     for(i=0;i<n;i++)
                     printf("%d ",VECT[i]);
     printf(" ]\n");
}

////////////////////////////////////
//      Print a Vector            //
///////////////////////////////////
void print_vect_C(complex float  *VECT, int n,char *name){
     int i;
     printf("\n %s= [ ",name);
     for(i=0;i<n;i++)
                     printf("%g +i %g ",creal(VECT[i]),cimag(VECT[i]));
     printf(" ]\n");
}
