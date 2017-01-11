#include "../defMacro.h"



///////////////////////////////////////////////////////////////////
//  Transforme une matrice de la base  locale dans la base propre //
///////////////////////////////////////////////////////////////////
void real_local2eigen(float *M, float *VP, int n)
{
    int i;
    float *M_temp, *VP_temp;
    
    float a = 1.0;
    float b = 0.0;
    
    // temporary matrix for multiplication
    M_temp = calloc(n*n,sizeof(float));
    VP_temp = calloc(n*n,sizeof(float));
    
    // copy the eigenvector matrix
    vectcopy(VP, VP_temp, n*n);
	
    // multiplication : M_temp = VP*M
    cblas_sgemm(CblasRowMajor,CblasNoTrans,CblasNoTrans,n,n,n,
    a,VP_temp,n,M,n,b,M_temp,n);
    
    // deuxieme multiplication: M = M_temp*VP'
    cblas_sgemm(CblasRowMajor,CblasNoTrans,CblasTrans,n,n,n,
    a,M_temp,n,VP_temp,n,b,M,n);
    
    free(M_temp);
    free(VP_temp);
}




///////////////////////////////////////////////////////////////////
//  Transforme une matrice de la base propre dans la base locale //
///////////////////////////////////////////////////////////////////
void real_eigen2local(float *M, float *VP, int n)
{
    int i;
    float *M_temp, *VP_temp;
    
    float a = 1.0;
    float b = 0.0;
    
    // temporary matrix for multiplication
    M_temp = calloc(n*n,sizeof(float));
    VP_temp = calloc(n*n,sizeof(float));
    
    // copy the eigenvector matrix
    vectcopy(VP, VP_temp, n*n);
	
    // multiplication : M_temp = VP*M
    cblas_sgemm(CblasRowMajor,CblasTrans,CblasNoTrans,n,n,n,
    a,VP_temp,n,M,n,b,M_temp,n);
    
    // deuxieme multiplication: M = M_temp*VP'
    cblas_sgemm(CblasRowMajor,CblasNoTrans,CblasNoTrans,n,n,n,
    a,M_temp,n,VP_temp,n,b,M,n);
    
    free(M_temp);
    free(VP_temp);
}
