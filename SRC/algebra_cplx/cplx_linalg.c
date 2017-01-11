#include "../defMacro.h"


//////////////////////////////////////////////////////////
//    CALCUL de l exponentielle a partir d un vecteur   //
//	contenant les valeurs propres du Hamiltinen	//
/////////////////////////////////////////////////////////
void expm_diag(complex float *EXPM, float *VECT_VP, int n, float *dT)
{
 	int i;	
	for(i=0;i<n;i++)
		EXPM[i*(n+1)] = cexp(-I*VECT_VP[i]*dT[0]);
	

}