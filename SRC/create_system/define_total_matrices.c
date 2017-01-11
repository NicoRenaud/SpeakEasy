#include "../defMacro.h"


void define_total_relaxation(float *G, float *R, int *index1, int *index2, SYS sys)
{
  
  int i,j,k=0;
  int n_dbl = (sys.nState+1)*sys.nState/2.;
  int nTot = 1 + sys.nState + (sys.nState+1)*sys.nState/2;

  // relaxation to the groud state
  for(i=0;i<sys.nState;i++)
  {
    G[1+i] = sys.grd_relax;
    G[(i+1)*nTot] = sys.grd_relax;
  }
  
  // relaxation from the double to the single
  for(i=0;i<sys.nState;i++)
  {
    for(j=i;j<sys.nState;j++)
    {
      G[ index1[i]*nTot+index2[k]] = sys.dbl2sglrelax;
      G[ index1[i]+index2[k]*nTot] = sys.dbl2sglrelax;
      G[ index1[j]*nTot+index2[k]] = sys.dbl2sglrelax;
      G[ index1[j]+index2[k]*nTot] = sys.dbl2sglrelax;
      k++;
    }
  }
  
  //intraband relaxation
  for(i=0;i<sys.nState;i++)
  {
    for(j=0;j<sys.nState;j++)
      G[index1[i]+index1[j]*nTot] = R[i+j*sys.nState];
    
  }
}


void define_total_dipole(float *U, float *D, float *D2, int *index1, int n1, int *index2, int n2)
{
  
  int i,j;
  int nTot = 1+n1+n2;
  
  
  // grd2spl
  for(i=0;i<(n1+1);i++)
  {
    for(j=0;j<(n1+1);j++)
    {
      U[i*nTot+j] = D[i*(n1+1)+j];
      U[j*nTot+i] = D[j*(n1+1)+i]; 
    }
  }
  
  
  //sgl2dbl
  for(i=0;i<n1;i++)
  {
    for(j=0;j<n2;j++)
    {
      U[index1[i]*nTot+index2[j]] = D2[i*n2+j];
      U[index2[j]*nTot+index1[i]] = D2[i*n2+j];
    }
  }
  
}