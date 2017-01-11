#include "../defMacro.h"

void spec_k1_23( float *W1, int nW1, float *W2, int nW2, float *T, int nT, float *E, float *G, float *U, int nTot, int *ind1, int n1, int *ind2, int n2, char *file_out)
{
  
  int iT;
  float t;
  int ep,e,f;
  int iw2=0,iw3=0;
  float w2,w3;
  complex float wa,wb,wt;
  float eta = pow(10,-8);
  complex float *Sgsb,*Sesa,*Sese,*Stot;
  complex float s;
  
  // memory allocation
  Sgsb = calloc(nW1*nW2,sizeof(complex float));
  Sesa = calloc(nW1*nW2,sizeof(complex float));
  Sese = calloc(nW1*nW2,sizeof(complex float));
  Stot = calloc(nW1*nW2,sizeof(complex float));  
  
  /////////////////////////////////
  // for all the time we want
  /////////////////////////////////
  for(iT=0;iT<nT;iT++)
  {
    t = T[iT];
  
    //////////////////////////////////
    // for all the first frequency
    //////////////////////////////////
    for(iw2=0; iw2<nW1 ;iw2++)
    {

      // current frequency
      w2 = W1[iw2];
      
      ////////////////////////////////////
      // for all the second frequency
      ////////////////////////////////////
      for(iw3=0; iw3<nW2; iw3++)
      {
	
	// current frequency
	w3 = W2[iw3];
	
	//////////////////////////////////////
	//	GROUND STATE BLEACHING
	//////////////////////////////////////
	
	// init the value
	s = 0.;
	
	// sum over single excited states
	for(ep=0;ep<n1;ep++)
	{
	  // sun over single excited states
	  for(e=0;e<n2;e++)
	  {
	    wb = abs(E[ind1[ep]] - E[0]) + I * G[ind1[ep]*nTot] + eta;	 
	    wt = abs(E[0] - E[ind1[e]]) +I*G[ind1[e]];
	    s -= U[ind1[ep]]*U[ind1[ep]*nTot]*U[ind1[e]]*U[ind1[e]*nTot]/( w3-wb ) / (w2+I*eta) * cexpf(I*wt*t);
	  } 
	}
	Sgsb[iw2*nW2+iw3] = s;

	
	//////////////////////////////////////
	//	Excited State emission
	//////////////////////////////////////	
	// init the value
	s = 0.;
	
	// sum over single excited states
	for(ep=0;ep<n1;ep++)
	{
	  // sun over single excited states
	  for(e=0;e<n2;e++)
	  {
	    wa = abs(E[ind1[ep]] - E[ind1[e]]) + I * G[ind1[ep]*nTot+ind1[e]] + eta;
	    wb = abs(E[ind1[ep]] - E[0]) + I * G[ind1[ep]*nTot] + eta;
	    wt = abs(E[0] - E[ind1[e]]) +I*G[ind1[e]];	    
	    s -= U[ind1[ep]]*U[ind1[ep]*nTot]*U[ind1[e]]*U[ind1[e]*nTot]/( w3-wb) / (w2-wa) *cexpf(I*wt*t);
	  } 
	}
	Sese[iw2*nW2+iw3] = s;
	
	
	//////////////////////////////////////
	//	Excited State absorbtion
	//////////////////////////////////////	
	// init the value
	s = 0.;
	
	// sum over the doubly excited states
	for(f=0;f<n2;f++)
	{
	  // sum over single excited states
	  for(ep=0;ep<n1;ep++)
	  {
	    // sun over single excited states
	    for(e=0;e<n2;e++)
	    {
	      wa = abs(E[ind1[ep]] - E[ind1[e]]) + I * G[ind1[ep]*nTot+ind1[e]] + eta;
	      wb = abs(E[ind2[f]] - E[ind1[e]]) + I * G[ind2[f]*nTot+ind1[e]] + eta;
	      wt = abs(E[0] - E[ind1[e]]) +I*G[ind1[e]];	    
	      s += U[ind1[ep]*nTot+ind2[f]]*U[ind2[f]*nTot+ind1[ep]]*U[ind1[e]]*U[ind1[ep]*nTot]/( w3-wb ) / (w2-wb) *cexpf(I*wt*t);
	    } 
	  }
	}
	Sesa[iw2*nW2+iw3] = s;
	
	
	//////////////////////////////////////
	//	Total signal
	//////////////////////////////////////	
        Stot[iw2*nW2+iw3] = Sese[iw2*nW2+iw3];// + Sese[iw2*nW2+iw3] + Sesa[iw2*nW2+iw3];
	
      }
    }
  
    
    //////////////////////////////////////
    //	EXPORT THE MAP
    //////////////////////////////////////
    export_scilab(Stot,W1,nW1,W2,nW2,T,iT,file_out);
   
  }
  
  
  // free memory
  free(Sesa);
  free(Sese);
  free(Sgsb);
  free(Stot);
  
}