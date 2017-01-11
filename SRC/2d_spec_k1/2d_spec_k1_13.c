#include "../defMacro.h"
#include "../output/export_scilab.h"


void spec_k1_13( float *W1, int nW1, float *W2, int nW2, float *T, int nT, 
		 float *E, float *G, float *U, int nTot, int *ind1, int n1, int *ind2, int n2, 
		 char *file_out)
{
  
  
  int iT;
  complex float time;
  int ep,e,f;
  int iw1=0,iw3=0;
  complex float w1,w3;
  complex float wa,wb,wt;
  complex float eta = pow(10,-8);
  complex float *Sgsb,*Sesa,*Sese,*Stot;
  complex float s;
  complex float arg;
  complex float dip;
  
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
    time = (complex float) T[iT];
    
    // where are we time wise
    printf("T : %f+i%f\n",crealf(time),cimagf(time));
    
    //////////////////////////////////
    // for all the first frequency
    //////////////////////////////////
    for(iw3=0; iw3<nW1 ;iw3++)
    {

      // current frequency
      w3 = (complex float) W1[iw3];
      
      ////////////////////////////////////
      // for all the second frequency
      ////////////////////////////////////
      for(iw1=0; iw1<nW2; iw1++)
      {
	
        // where are we on the map
        //printf("iw3 = %d/%d, iw1 = %d/%d\n",iw3,nW1,iw1,nW2);
        
        // current frequency
        w1 = (complex float) W2[iw1];
	
        // init the map at this point
        Stot[iw3*nW1+iw1] = 0;

	
        //////////////////////////////////////
        //	GROUND STATE BLEACHING
        //////////////////////////////////////
	    
        // init the value
        s = 0.;
	    
        // sum over single excited states
        for(ep=0;ep<n1;ep++)
        {
          // sun over single excited states
          for(e=0;e<n1;e++)
          {
            wa = (complex float) (E[ind1[ep]] - E[0]) + I * G[ind1[ep]*nTot] + eta;
            wb = (complex float) (E[ind1[e]]-E[0]) + I * G[ind1[e]*nTot] + eta;
            dip = (complex float) U[ind1[ep]]*U[ind1[ep]*nTot]*U[ind1[e]]*U[ind1[e]*nTot];
            s -= dip / (w3-wa) / (w1-wb);
          }
        }
        Sgsb[iw3*nW1+iw1] = s;
        
	    
        //////////////////////////////////////
        //	Excited State emission
        //////////////////////////////////////
        // init the value
        s = 0.;
	    
        // sum over single excited states
        for(ep=0;ep<n1;ep++)
        {
          // sum over single excited states
          for(e=0;e<n1;e++)
          {
            
            wa = (complex float) fabs(E[ind1[ep]] - E[0]) + I * G[ind1[ep]*nTot] + eta;
            wb = (complex float) fabs(E[ind1[e]]-E[0]) + I * G[ind1[e]] + eta;
            wt = (complex float) fabs(E[ind1[ep]] - E[ind1[e]]) + I*G[ind1[ep]*nTot+ind1[e]];
            dip = (complex float) U[ind1[ep]]*U[ind1[ep]*nTot]*U[ind1[e]]*U[ind1[e]*nTot];
            //arg = cexp(I*wt*time);
            //printf("wt = %f +i %f\n",crealf(wt*time),cimagf(wt*time));
            //printf("arg = %f +i %f\n",crealf(arg),cimagf(arg));
            s -= dip /( w3 - wa ) / (w1-wb) * cexp(I*wt*time);
          }
        }
        Sese[iw3*nW1+iw1] = s;
	    
	    
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
            for(e=0;e<n1;e++)
            {
              wa = (complex float) fabsf(E[ind2[f]] - E[ind1[e]]) + I * G[ind2[f]*nTot+ind1[e]] + eta;
              wb = (complex float) fabsf(E[0] - E[ind1[e]]) + I * G[ind1[e]] + eta;
              wt = (complex float) fabsf(E[ind1[ep]] - E[ind1[e]]) +I*G[ind1[ep]*nTot+ind1[e]];
              dip = (complex float) U[ind1[e]*nTot+ind2[f]]*U[ind2[f]*nTot+ind1[ep]]*U[ind1[e]]*U[ind1[ep]*nTot];
              s += dip /( w3-wa ) / (w1-wb) * cexpf(I*wt*time);
            }
          }
        }
        Sesa[iw3*nW1+iw1] = s;
	    
	    
        //////////////////////////////////////
        //	Total signal
        //////////////////////////////////////
        Stot[iw3*nW1+iw1] += Sgsb[iw3*nW1+iw1] + Sese[iw3*nW1+iw1] + Sesa[iw3*nW1+iw1];
    
      }
    }
  
    
    //////////////////////////////////////
    //	EXPORT THE MAP
    //////////////////////////////////////
    export_gnuplot(Stot,W1,nW1,W2,nW2,T,iT,file_out);
  }
  
  
  // free memory
  free(Sesa);
  free(Sese);
  free(Sgsb);
  free(Stot);
}