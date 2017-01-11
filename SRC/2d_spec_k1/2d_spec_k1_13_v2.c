#include "../defMacro.h"

void spec_k1_13_broad( float *W1, int nW1, float *W2, int nW2, float *T, int nT, 
		 float *E0, float *G, float *U, int nTot, int *ind1, int n1, int *ind2, int n2, 
		 SYS sys, char *file_out)
{
  
  int i;
  int iT;
  float t;
  int ep,e,f;
  int iw1=0,iw3=0;
  complex float w1,w3;
  int ireal;
  float *E,*ETOT;
  complex float wa,wb,wt;
  float eta = pow(10,-8);
  complex float *Stot;
  complex float s_ese, s_gsb, s_esa;
  const gsl_rng_type *T_fluct;
  gsl_rng *r_fluct;
  complex float signal;
  double fluct;
  int nreal = sys.disorder_nReal;
  double amp_dbl = (double) sys.disorder_amp;
  int shift;
  int rn;
  
  
  // memory allocation
  Stot = calloc(nW1*nW2,sizeof(complex float));  
  ETOT = calloc(nreal*nTot,sizeof(float));
  E = calloc(nTot,sizeof(float));

  
   // init the seed for disorder
   T_fluct = gsl_rng_default;
   r_fluct = gsl_rng_alloc(T_fluct);
   
    // initalise the random numbe generrator
    srand(time(NULL));
    
    // compute new value of energies according to disorder
   for(ireal=0;ireal<nreal;ireal++)
   {
      shift = ireal*nTot;
      for(i=1;i<nTot;i++)
      {
	 rn = rand();
	 gsl_rng_set(r_fluct,rn);
         fluct = gsl_ran_gaussian(r_fluct,amp_dbl);
         ETOT[shift+i] = E0[i] + (float) fluct;
      }
   }

  /////////////////////////////////
  // for all the time we want
  /////////////////////////////////
  for(iT=0;iT<nT;iT++)
  {
    t = T[iT];
 
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
	
	// current frequency
	w1 = (complex float) W2[iw1];
	
	// init the map at this point
	Stot[iw3*nW1+iw1] = 0;
	
	//////////////////////////////////////////////
	//	inomogeneous broadening
	//////////////////////////////////////////////
	for(ireal=0;ireal<nreal;ireal++)
	{
	  
	    // grap the good energies
	    for(i=0;i<nTot;i++)
	      E[i] = ETOT[ i+ireal*nTot ];


	    
	    // init the value
	    s_ese = 0.;
	    s_gsb = 0.;
	    s_esa = 0.;
	    
	    //////////////////////////////////////////////
	    // sum over single excited states
	    //////////////////////////////////////////////
	    for(ep=0;ep<n1;ep++)
	    {
	      ///////////////////////////////////////////////
	      // sun over single excited states
	      ///////////////////////////////////////////////
	      for(e=0;e<n1;e++)
	      {
		
		//////////////////////////////////////
		//	Ground state bleaching
		//////////////////////////////////////
		if(!strcmp(sys.GSB,"yes"))
		{
		  wa = (complex float) fabs(E[ind1[ep]] - E[0]) - I * G[ind1[ep]*nTot] + eta;
		  wb = (complex float) fabs(E[0] - E[ind1[e]]) - I * G[ind1[e]] + eta;	
		  //printf("wa = %f+i%f\t wb = %f+i%f \n",crealf(wa),cimagf(wa),crealf(wb),cimagf(wb));
		  s_gsb -= U[ind1[ep]]*U[ind1[ep]*nTot]*U[ind1[e]]*U[ind1[e]*nTot]/( w3-wa ) / (w1-wb);	
		}

		
		//////////////////////////////////////
	        //	Excited State emission
	        //////////////////////////////////////
		if(!strcmp(sys.ESE,"yes"))
		{
		  wa = fabs(E[ind1[ep]] - E[0]) - I * G[ind1[ep]*nTot] + eta;
		  wb = fabs(E[0] - E[ind1[e]]) - I * G[ind1[e]] + eta;
		  		  //printf("wa = %f+i%f\t wb = %f+i%f \n",crealf(wa),cimagf(wa),crealf(wb),cimagf(wb));
		  wt = fabs(E[ind1[ep]] - E[ind1[e]]) - I*G[ind1[ep]*nTot+ind1[e]];	    
		  s_ese -= U[ind1[ep]]*U[ind1[ep]*nTot]*U[ind1[e]]*U[ind1[e]*nTot]/( w3-wa ) / (w1-wb) * cexp(-I*wt*t);
		}

		
		//////////////////////////////////////
		//	Excited State absorbtion
		//////////////////////////////////////
		if(!strcmp(sys.ESA,"yes"))
		{
		  for(f=0;f<n2;f++)
		  {
		      wa = fabs(E[ind2[f]] - E[ind1[e]]) - I * G[ind2[f]*nTot+ind1[e]] + eta;
		      wb = fabs(E[0] - E[ind1[e]]) - I * G[ind1[e]] + eta;
		      		 // printf("wa = %f+i%f\t wb = %f+i%f \n",crealf(wa),cimagf(wa),crealf(wb),cimagf(wb));
		      wt = fabs(E[ind1[ep]] - E[ind1[e]]) - I*G[ind1[ep]*nTot+ind1[e]];	    
		      s_esa += U[ind1[e]*nTot+ind2[f]]*U[ind2[f]*nTot+ind1[ep]]*U[ind1[e]]*U[ind1[ep]*nTot]/( w3-wa ) / (w1-wb) *cexp(-I*wt*t);	    
		  }
		}
	      }  // end loop over second subspace
	    } // end loop over first subspace
	    
	    
	    //////////////////////////////////////
	    //	Total signal
	    //////////////////////////////////////	
	    signal = (s_gsb + s_ese + s_esa)/(float) nreal;
	    if(nreal>1)
	      Stot[iw3*nW1+iw1] += sqrtf(signal*conjf(signal));
	    else
	      Stot[iw3*nW1+iw1] += signal;

	    
	} // end loop static disorder
      } // end loop second frequency
    } // end loop first frequency
  
    
    //////////////////////////////////////
    //	EXPORT THE MAP
    //////////////////////////////////////
    export_scilab(Stot,W1,nW1,W2,nW2,T,iT,file_out,sys.unit);
    printf(" %d/%d map computed : %s%d.sci\n",iT+1,nT,file_out,iT+1);
  }
  
  
  // free memory
  free(Stot);
  free(ETOT);
  free(E);
  gsl_rng_free(r_fluct);
}
