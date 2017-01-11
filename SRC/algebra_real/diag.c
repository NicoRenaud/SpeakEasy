#include "../defMacro.h"


/////////////////////////////////////////////////////////
//               Diagonalisation                       //
/////////////////////////////////////////////////////////

void spec(float *VECT_PRP, float *VAL_PRP, float *MAT, int n) {


	float  *work=NULL, *w=NULL;
        int lwork,info,i,j,k=0;

	// allocation memoire
	work = (float *)malloc(1*sizeof(float));

	// copie de la matrice dans a forme vectorielle
	for(i=0;i<n*n;i++)
		VECT_PRP[i] = MAT[i];


	// precalcul du lwork optimal
	lwork=-1;
        ssyev_( "N", "U", &n, VECT_PRP, &n, VAL_PRP, work, &lwork, &info );
	lwork= work[0];

	// realocation de work
        free(work);
        work = (float *)malloc(lwork*sizeof(float));

	//calcul des vecteurs/valeurs propres;
         ssyev_( "V", "U", &n, VECT_PRP, &n, VAL_PRP, work, &lwork, &info );


	//free work
	free(work);

}
