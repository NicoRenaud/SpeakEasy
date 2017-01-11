#include "../defMacro.h"


/////////////////////////////////////////////////////////
//       Copie une matrice dans une autre  COMPLEXE     //
/////////////////////////////////////////////////////////
void vectcopy_C(complex float*vect, complex float *vect_copy, int n)
{
	int i;
	for(i=0;i<n;i++)
		vect_copy[i] = (complex float) vect[i];

}
