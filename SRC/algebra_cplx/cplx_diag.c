
#include "../defMacro.h"

//////////////////////////////////////////////////////
//    Comoute eigenvalues and eigenvectors		//
// 	of a complex general matrix			//
/////////////////////////////////////////////////////////
void spec_complex(complex float *vect_prp_left, complex float *vect_prp_right, complex float *val_prp, complex float *Mat, int nState)
{

//   printf("======================================== \n");
//   printf("==	START DIAG \n");
//   printf("======================================== \n"); 
//   print_mat_C(Mat,nState,nState,"Minit");
  
  // variable pour diagonalisation de marice complexe
  int i;
  complex float wkopt;
  complex float *work;
  int lwork,info;
  complex float *VP2; 
  float  rwork[2*nState];
  
  VP2 = calloc(nState*nState,sizeof(complex float ));
  
  // precalcul du lwork optimal
  lwork = -1;
  cgeev_( "Vectors", "Vectors", &nState, Mat, &nState, val_prp, vect_prp_left, &nState, vect_prp_right, &nState,
         &wkopt, &lwork, rwork, &info );

  // reallocation of the temp variable
  lwork = (int)creal(wkopt);
  work = (complex float  *) calloc( lwork,sizeof(complex float ) );

  // eigenvalue calculation
  cgeev_( "Vectors", "Vectors", &nState, Mat, &nState, val_prp, vect_prp_left, &nState, vect_prp_right, &nState,
	  work, &lwork, rwork, &info );

  free(work);
}
