#include "../defMacro.h"




/////////////////////////////////////////////////////////
//  		linear spaced vector		       //
/////////////////////////////////////////////////////////
void linspace(float *V, float a, float b, int n)
{
  int i;
  float dV = (b-a)/(n-1);
  
  for(i=0;i<n;i++)
    V[i] = a+i*dV;
}


/////////////////////////////////////////////////////////
//  Transforme une matrice float en matrice complex    //
/////////////////////////////////////////////////////////
void reinitVect(float *V,int size)
{
    int i;
    for(i=0;i<size;i++)
      V[i] = 0.;
}


////////////////////////////////////////////////////////
//      Cree une matrice identite de taille n          //
/////////////////////////////////////////////////////////
void eye(float *Id, int n)
{

	int i,j;
	for(i=0;i<n;i++)
	{
		Id[i*(n+1)] = 1.;
	}
}

///////////////////////////////////////////////////////////////////
//      Cree une matrice diagonale a partir d un vecteur         //
///////////////////////////////////////////////////////////////////

void diagonal(float *Vs_mat,float *Vs,int nState)
{
    int i;
    for(i=0;i<nState;i++)
	Vs_mat[i*(nState+1)] = Vs[i];
    
}

///////////////////////////////////////////////////////////////////
//      Check if the matix is hermitian and correct it if not    //
///////////////////////////////////////////////////////////////////
void check_hermitian_real(float *H,int size)
{
  
 int i,j;
 float a,b,c;
 float err=0.;
 
 // for all the elements in the Hamiltonian
 for(i=0;i<size;i++)
 {
   
  for(j=i+1;j<size;j++)
  {
   
      // the two elements checked right now
      a = H[i*size+j];
      b = H[j*size+i];
      
      // if they are different
      if(a!=b) 
      {
	// store the error
	err += fabs(a-b);
	
	// mean value
	c = (a+b)/2;
	
	// replace
	H[i*size+j] = c;
	H[j*size+i] = c;
      }
  }  
 }
  if(err>0)
    printf("Warning : Hamiltonian modified for hermiticity reasons: error = %f\n",err);
}


