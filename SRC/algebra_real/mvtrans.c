#include "../defMacro.h"


/////////////////////////////////////////////////////////
//       Passage d une matrice en forme vecteur         //
/////////////////////////////////////////////////////////
void mat2vect(float **mat,float *vect,int n)
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
void vect2mat(float *vect,float **mat,int n)
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
