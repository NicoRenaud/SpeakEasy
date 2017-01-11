#include "defMacro.h"



#include "./algebra_cplx/cplx_copy.h"
#include "./algebra_cplx/cplx_rotatebasis.h"
#include "./algebra_cplx/cplx_mvtrans.h"
#include "./algebra_cplx/cplx_gen.h"
#include "./algebra_cplx/cplx_linalg.h"
#include "./algebra_cplx/cplx_inv.h"



#include "./algebra_real/rotatebasis.h"
#include "./algebra_real/copy.h"
#include "./algebra_real/diag.h"
#include "./algebra_real/mvtrans.h"
#include "./algebra_real/gen.h"

#include "./input/read_hamiltonian.h"
#include "./input/read_input_file.h"
#include "./input/convert.h"

#include "./output/export_scilab.h"
#include "./output/print_screen.h"

#include "./create_system/define_matrices.h"
#include "./create_system/define_total_matrices.h"

//#include "./disorder/disorder.h"

#include "./2d_spec_k1/spec.h"



///////////////////////////////////////////////////////////
////////					///////////
////////	MAIN FUNCTION			///////////
////////					///////////
///////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
  
  ///////////////////////////////////////////////////////////
  //               Declaration des varialbles              //
  ///////////////////////////////////////////////////////////
    
  // donnes du systeme
  SYS sys;
  
  // Hamiltonian Relaxation Dipole (simply excited subspace)
  float *H, *R, *D, *D2; 
  
  // data on the ground/simply excited/doubly excited subpsaces (Energies, Relaxation, Dipole)
  float *E, *G, *U;
  int n_dbl_xtd, nTot;
  
  // indexes of the different subspace
  int *ind1, *ind2;
  
  // Evolution time
  float *TIME;
  
  // frequency domains
  float *W1, *W2;
  
  // generic
  int i;
  
  
  ///////////////////////////////////////////////////////////
  //     Define the path to read the input data            //
  ///////////////////////////////////////////////////////////
  
  // input file
  char IN_PATH[100];
  strcpy(IN_PATH,argv[1]);
  strcat(IN_PATH,"/in.dat");

  //Hamiltonian path
  char PATH_H[100];
  strcpy(PATH_H,argv[1]);
  
  //relaxation path
  char PATH_R[100];
  strcpy(PATH_R,argv[1]);
  
  //dipole path
  char PATH_D[100];
  strcpy(PATH_D,argv[1]);
  
  //dipole path
  char PATH_D2[100];
  strcpy(PATH_D2,argv[1]);
  
  // outfile
  char OUT_PATH[100];
  strcpy(OUT_PATH,argv[2]);
  strcat(OUT_PATH,"2dmap_");
  
  
  
  ///////////////////////////////////////////////////////////
  //    	Read the main input files    		   //
  ///////////////////////////////////////////////////////////
  
  // read input file
  read_main_input(&sys, IN_PATH);
  print_header(sys);
 
  
  // total size
  n_dbl_xtd = (sys.nState+1)*sys.nState/2.;
  nTot = 1 + sys.nState + n_dbl_xtd;
  
  ///////////////////////////////////////////////////////////
  //    	Main memory allocation   		   //
  ///////////////////////////////////////////////////////////
  
  // Hamiltonian on sgl excited subspace
  H = calloc(sys.nState*sys.nState,sizeof(float));
  
  // intraband (sgl excited) relaxation matrix
  R = calloc(sys.nState*sys.nState,sizeof(float));
  
  // dipole grd to sgl excited 
  D = calloc((sys.nState+1)*(sys.nState+1),sizeof(float));
  
  // dipole sgl to dbl excited
  D2 = calloc(sys.nState*n_dbl_xtd,sizeof(float));
  
  // frequency range
  W1 = calloc(sys.nW1,sizeof(float));
  W2 = calloc(sys.nW2,sizeof(float));
  
  // evolution time
  TIME = calloc(sys.nDiv,sizeof(float));
  
  // indexes
  ind1 = calloc(sys.nState,sizeof(int));
  ind2 = calloc(n_dbl_xtd,sizeof(int));
  
  // total energy grd/sgl/dbl
  E = calloc(nTot,sizeof(float));
  
  // total relaxation
  G = calloc(nTot*nTot,sizeof(float));
  
  // total dipole
  U = calloc(nTot*nTot,sizeof(float));
  
  ///////////////////////////////////////////////////////////
  //    	Define the vector for Spectro		   //
  ///////////////////////////////////////////////////////////
  

  
  // define the vectors
  linspace(W1,sys.minW1,sys.maxW1,sys.nW1);
  linspace(W2,sys.minW2,sys.maxW2,sys.nW2);
  linspace(TIME,sys.t0,sys.tmax,sys.nDiv);
  
  // convert into eV if necessary
  if(!strcmp(sys.unit,"WN"))
  {
   wn2ev(W1,sys.nW1);
   wn2ev(W2,sys.nW2);
   wn2ev_sys(&sys);
  }
  

  
  ///////////////////////////////////////////////////////////
  //    	Define the indexes for simple		   //
  //		and double excited subspace		   //
  ///////////////////////////////////////////////////////////
  
  // index of state
  for(i=0;i<sys.nState;i++)
    ind1[i] = i+1;
  
  for(i=0;i<n_dbl_xtd;i++)
    ind2[i] = i+sys.nState+1;


  
  ///////////////////////////////////////////////////////////
  //    	Read/define the  Hamiltonian 		   //
  // 	       realxation and Dipole matrix                //
  ///////////////////////////////////////////////////////////

  //=================================
  // HAMILTONIAN MATRIX
  //=================================
  strcat(PATH_H,sys.hmltn_mat);
  read_mat(H, sys.nState,sys.nState, PATH_H,"sym");
  if(!strcmp(sys.unit,"WN"))
    wn2ev(H,sys.nState*sys.nState);
    
  //=================================
  // DIPOLE MATRICES GRD 2 SGL
  //=================================
    
  // if one is define in in.dat read it
  if(strcmp(sys.dipole_mat,"none"))
  {
    strcat(PATH_D,sys.dipole_mat);
    read_mat(D, sys.nState+1,sys.nState+1, PATH_D,"sym");
  }
  // otherwise define it from the overlap matrix and the dipole intensity
  else
    define_grd2sgl_dipole(D,H,sys.nState,sys.grd2sgl_dipole,sys.grd2sgl_freq,sys.grd2sgl_width);
  
  
  //=================================
  // DIPOLE MATRICES SGL 2 DBL
  //=================================
    
  // if one is define in in.dat read it
  if(strcmp(sys.dipole_mat_2,"none"))
  {
    strcat(PATH_D2,sys.dipole_mat_2);
    read_mat(D2, sys.nState,n_dbl_xtd, PATH_D2,"asym");
  }
  // otherwise define it from the overlap matrix and the dipole intensity
  else
    define_sgl2dbl_dipole(D2,E, ind1, sys.nState, ind2, n_dbl_xtd, sys.sgl2dbl_dipole, sys.sgl2dbl_freq, sys.sgl2dbl_width);
  

  //=====================================
  // RELAXATION MATRIX SGL 2 SGL
  //=====================================
  
  // if one is define in in.dat read it
  if(strcmp(sys.relax_mat,"none"))
  {
    strcat(PATH_R,sys.relax_mat);
    read_mat(R, sys.nState,sys.nState, PATH_R,"asym");
  }
  // otherwise define it from the overlap matrix 
  // and the relaxation intensity
  else
  {
    define_relax_from_h(R,H,sys.simply_relax,sys.nState,sys.temp);
    define_dephas(R, H, sys.simply_relax, sys.nState, sys.simply_dephas,sys.temp);
  }

  
  
  ///////////////////////////////////////////////////////////
  //    	Define the data over the total		   //
  //		system space (grd/single/double)	   //
  ///////////////////////////////////////////////////////////
  
  // compute energies
  compute_energies(E,H,sys.nState);
  

  // define the total relaxation matrix
  define_total_relaxation(G, R, ind1, ind2, sys);
  
  //define the total dipole matrix
  define_total_dipole(U, D, D2, ind1, sys.nState, ind2, n_dbl_xtd);
  
  
  
  ///////////////////////////////////////////////////////////
  //    	PRINT THE MATRICES BY CURIOSISTY	   //
  //////////////////////////////////////////////////////////
  if(1)
  {
    print_vect_int(ind1,sys.nState,"ind1");
    print_vect_int(ind2,n_dbl_xtd,"ind2");
    print_mat(H,sys.nState,sys.nState,"H");
    print_mat(R,sys.nState,sys.nState,"R");
    print_mat(D,sys.nState+1,sys.nState+1,"D");
    print_mat(D2,sys.nState,n_dbl_xtd,"D2");
    print_mat(E,nTot,1,"E");
    print_mat(G,nTot,nTot,"G");
    print_mat(U,nTot,nTot,"U");
  } 
  
  ///////////////////////////////////////////////////////////
  //    	Compute the optical signal in the	   //
  //  		direction and phase matching desired	   //
  ///////////////////////////////////////////////////////////
    
  // compute the map
  spec_k1_13(W1,sys.nW1,W2,sys.nW2,TIME,sys.nDiv,E, G,U,nTot,ind1, sys.nState,ind2, n_dbl_xtd, OUT_PATH);
  
  
  ///////////////////////////////////////////////////////////
  //    	PRINT THE END OF FILE                            //
  ///////////////////////////////////////////////////////////
  print_end(argv[2], OUT_PATH, sys.nDiv); 
  
  
  
  ///////////////////////////////////////////////////////////
  //    	Free the memeory because we re cool        //
  ///////////////////////////////////////////////////////////
  
  
  // free memory
  free(H);
  free(R);
  free(D);
  free(D2);
  free(E);
  free(U);
  free(G);
  free(W1);
  free(W2);
  free(TIME);
  free(ind1);
  free(ind2);

  //return
  return 0;
}
