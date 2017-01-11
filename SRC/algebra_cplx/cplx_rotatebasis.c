#include "../defMacro.h"



//////////////////////////////////////////////////////////
//      Change a Operator from its diagonal basis	 //
//		to its local basis set			//
//		M <-- VP*M*VP' 				//
//////////////////////////////////////////////////////////
void cplx_eigen2local(complex float *M, float *VP, int n)
{
    int i;
    complex float *VP_cplx;
    complex float *M_temp;
    
    float a[2] = {1.0,0.0};
    float b[2] = {0.0,0.0};
    
    VP_cplx = calloc(n*n,sizeof(complex float));
    M_temp = calloc(n*n,sizeof(complex float));
    dbl2cplx(VP_cplx, VP, n*n);
    
	
    cblas_cgemm(CblasRowMajor,CblasConjTrans,CblasNoTrans,n,n,n,
    a,VP_cplx,n,M,n,
    b,M_temp,n);
	
    cblas_cgemm(CblasRowMajor,CblasNoTrans,CblasNoTrans,n,n,n,
    a,M_temp,n,VP_cplx,n,b,M,n);
    
    free(M_temp);
    free(VP_cplx);
}


//////////////////////////////////////////////////////////
//      Change a Operator from its local basis	 //
//		to its eigen basis set			//
//		M <-- VP*M*VP' 				//
//////////////////////////////////////////////////////////
void cplx_local2eigen(complex float *M, float *VP, int n)
{
  
  

    int i;
    complex float *VP_cplx;
    complex float *M_temp;
    

    float a[2] = {1.0,0.0};
    float b[2] = {0.0,0.0};
    
    
    M_temp = calloc(n*n,sizeof(complex float));
    VP_cplx = calloc(n*n,sizeof(complex float));

    dbl2cplx(VP_cplx, VP, n*n);

   
    cblas_cgemm(CblasRowMajor,CblasNoTrans,CblasNoTrans,n,n,n,
    a,VP_cplx,n,M,n,
    b,M_temp,n);
	
    
    cblas_cgemm(CblasRowMajor,CblasNoTrans,CblasConjTrans,n,n,n,
    a,M_temp,n,VP_cplx,n,b,M,n);
    
    
   free(M_temp);
   free(VP_cplx);
}

