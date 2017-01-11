#include "../defMacro.h"



/////////////////////////////////////////////////////////
//       Copie une matrice dans une autre              //
/////////////////////////////////////////////////////////
void vectcopy(float *vect, float *vect_copy, int n)
{
	int i;
	for(i=0;i<n;i++)
		vect_copy[i] = vect[i];

}


/////////////////////////////////////////////////////////
//       Copie une matrice dans une autre              //
/////////////////////////////////////////////////////////
void matcopy(float **mat, float **mat_copy,int n)
{

	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			mat_copy[i][j] = mat[i][j];
		}
	}
}
