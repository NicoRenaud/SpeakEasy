#include "../defMacro.h"


//////////////////////////////////////////////////////////
//     Compute the inverse of a matrix		//
//////////////////////////////////////////////////////////
void invMatComp(complex float *M_INV, complex float *M_OR, int size)
{
  
    int i,j;
    int n= size;
    int lwork, info, lwork2;
    complex float wkopt;
    complex float *work;
    int pivot[size];
    
    // copie de la matrice originale    
    for(i=0;i<n;i++)
    {
      for(j=0;j<n;j++)
	M_INV[i*size+j] = M_OR[i*size+j];
    }
    
    // LU factorisation of the matrix
    cgetrf_(&n, &n, M_INV, &n, pivot, &info);
    
    // optimal work computation 
    lwork = -1;
    cgetri_(&n, M_INV, &n, pivot, &wkopt, &lwork, &info);
    
    
    // memory allocation 
    lwork = (int) crealf(wkopt);
    work = (complex float *) calloc(lwork,sizeof(complex float) );
    
    // invert the matrix   
    cgetri_(&n, M_INV, &n, pivot, work, &lwork, &info);
    
    free(work);
  
}
