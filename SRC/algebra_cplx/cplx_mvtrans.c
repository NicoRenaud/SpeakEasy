#include "../defMacro.h"



//////////////////////////////////////////////////////////
//     Compute the transpose of a matrix		//
//////////////////////////////////////////////////////////
void transMat(complex float *M_TR, complex float *M_OR, int size)
{ 
  int i,j;
  for(i=0;i<size;i++)
  {
    for(j=0;j<size;j++)
      M_TR[i+j*size] = M_OR[i*size+j];
  }
}




/////////////////////////////////////////////////////////
//       Passage d une matrice en forme vecteur         //
/////////////////////////////////////////////////////////
void mat2vect_cplx(complex float**mat,complex float *vect,int n)
{
	int i,j,k=0;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			vect[k] = mat[i][j];
			k++;
		}
	}
}

////////////////////////////////////////////////////////
//       Passage d une vecteur en forme matrice         //
/////////////////////////////////////////////////////////
void vect2mat_cplx(complex float *vect,complex float **mat,int n)
{
	int i,j,k=0;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			mat[i][j] = vect[k];
			k++;
		}
	}
}
