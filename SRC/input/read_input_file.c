#include "../defMacro.h"


void read_main_input(SYS *sys, char *file_name)
{

   int INT;
   float FLT;
   float K;
   char str[100];
   char str2[10];
   char str8[10];
   char str9[20];
   char str_cmt[3];
   FILE *f;

   
   ////////////////////////
   // default values: system
   /////////////////////////   
   
   // number of states
   sys->nState = 1;
   
   // evolution time
   sys->t0 = 0;
   sys->tmax = 10;
   sys->nDiv = 100;
   
   // frequency domain
   sys->minW1 = 0.;
   sys->maxW1 = 1.;
   sys->nW1 = 10;
   sys->minW2 = 0.;
   sys->maxW2 = 1.;
   sys->nW2 = 10;
   
   // matrix pathway
   strcpy(sys->hmltn_mat,"none");
   strcpy(sys->relax_mat,"none");
   strcpy(sys->dipole_mat,"none");
   strcpy(sys->dipole_mat_2,"none");
   
   // energy unit
   strcpy(sys->unit,"eV");
   
   // relaxation constant
   sys->grd_relax = 0;
   sys->dbl2sglrelax = 0.;

   // dipole constant
   sys->grd2sgl_dipole = 0.;
   sys->grd2sgl_freq = 0.;
   sys->grd2sgl_width = 0.;

   
   // static disorder
   sys->disorder_amp = 0;
   sys->disorder_nReal = 0;
   
   // matrix pathway
   strcpy(sys->GSB,"yes");
   strcpy(sys->ESE,"yes");
   strcpy(sys->ESA,"yes");
 

    


   ////////////////////////
   // open the file
   /////////////////////////
   f = fopen(file_name,"r");
   if (!f) {
      printf("couldn't read %s\n", file_name);
      exit(1);
   }

   //////////////////////////////////////////
   // for all lines of the input file
   //////////////////////////////////////////
   while (!feof(f))
   {
        ///////////////////////
	// read the string
	///////////////////////
	fscanf(f,"%s",str);

	
	////////////////////////
	// if it's a comment
	////////////////////////
	strncpy(str_cmt,str,2);
	str_cmt[2] = '\0';
	if (!strcmp(str_cmt,"//"))
	  fgets(str,100,f);
	
	///////////////////////////
	// if it's not a comment
	///////////////////////////
	else
	{
	  
	  //////////////////////////////////
	  // determine what is the input
	  /////////////////////////////////

///////////////////////////////////////////////////////////////////////////
//				SYSTEM
///////////////////////////////////////////////////////////////////////////

	    ////////////////////////
	    // number of states
	    ///////////////////////    
	     if( !strcmp(str,"nState")            || 
	        !strcmp(str,"number_of_state")   || 
		!strcmp(str,"number_of_states")  || 
		!strcmp(str,"NUMBER_OF_STATES")  ||
	        !strcmp(str,"NSTATE")	)
	    {  
		  fscanf(f,"%d",&INT);		  
		  sys->nState = INT;
	    }
		  
		  
		  
	    ////////////////////////
	    // hamiltonian matrix
	    ///////////////////////    
	     else if( !strcmp(str,"hamiltonian")       ||
		      !strcmp(str,"HAMILTONIAN")	) 
	    {
		  fscanf(f,"%s",str9);		  
		  strcpy(sys->hmltn_mat,str9);
	    }
	    
	    
	    ////////////////////////
	    // relaxation matrix
	    ///////////////////////    
	     else if( !strcmp(str,"sgl_2_sgl_relax")       ||
		      !strcmp(str,"RELAX_PATH")	) 
	    {
		  fscanf(f,"%s",str9);		  
		  strcpy(sys->relax_mat,str9);
	    }
	    
	    ////////////////////////
	    // dipole matrix
	    ///////////////////////    
	     else if( !strcmp(str,"grd_2_sgl_dipole")       ||
		      !strcmp(str,"GRD_2_SGL_DIPOLE")	) 
	    {
		  fscanf(f,"%s",str9);		  
		  strcpy(sys->dipole_mat,str9);
	    }
	    
	    ////////////////////////
	    // dipole matrix
	    ///////////////////////    
	     else if( !strcmp(str,"sgl_2_dbl_dipole")       ||
		      !strcmp(str,"SGL_2_DBL_DIPOLE")	) 
	    {
		  fscanf(f,"%s",str9);		  
		  strcpy(sys->dipole_mat_2,str9);
	    }
		  
	    ////////////////////////
	    // unit energy
	    ///////////////////////    
	     else if( !strcmp(str,"unit_energy") ) 
	    {
		  fscanf(f,"%s",str2);		  
		  strcpy(sys->unit,str2);
	    }
		 
	    ////////////////////////
	    // temperature
	    ///////////////////////    
	     else if( !strcmp(str,"temperature") ) 
	    {
		  fscanf(f,"%f",&FLT);		  
		  sys->temp = FLT;
	    }	
	    
	    ////////////////////////
	    // relaxation to the ground
	    ///////////////////////    
	     else if( !strcmp(str,"sgl_2_grd_relax") ) 
	    {
		  fscanf(f,"%f",&FLT);		  
		  sys->grd_relax = FLT;
	    }
	    
	    ///////////////////////
	    // intra band (simply excited) relaxation magnitude
	    ///////////////////////    
	     else if( !strcmp(str,"intraband_relaxation") ) 
	    {
		  fscanf(f,"%f",&FLT);		  
		  sys->simply_relax = FLT;
	    }
	    
	    ///////////////////////
	    // intra band (simply excited) dephasing magnitude
	    ///////////////////////    
	     else if( !strcmp(str,"intraband_dephasing") ) 
	    {
		  fscanf(f,"%f",&FLT);		  
		  sys->simply_dephas = FLT;
	    }
	
	    ///////////////////////
	    // intra band (simply excited) dephasing magnitude
	    ///////////////////////    
	     else if( !strcmp(str,"dbl_2_sgl_relax") ) 
	    {
		  fscanf(f,"%f",&FLT);		  
		  sys->dbl2sglrelax = FLT;
	    }
	    
	    ///////////////////////
	    // frequency 1 min
	    ///////////////////////    
	     else if( !strcmp(str,"min_w1") ) 
	    {
		  fscanf(f,"%f",&FLT);		  
		  sys->minW1= FLT;
	    }
	    
	    ///////////////////////
	    // frequency 1 maz
	    ///////////////////////    
	     else if( !strcmp(str,"max_w1") ) 
	    {
		  fscanf(f,"%f",&FLT);		  
		  sys->maxW1= FLT;
	    }
	    
	    ///////////////////////
	    // frequency 1 resolution
	    ///////////////////////    
	     else if( !strcmp(str,"nb_w1") )
	    {
		  fscanf(f,"%d",&INT);		  
		  sys->nW1= INT;
	    }
	    
	     ///////////////////////
	    // frequency 1 min
	    ///////////////////////    
	     else if( !strcmp(str,"min_w2") ) 
	    {
		  fscanf(f,"%f",&FLT);		  
		  sys->minW2= FLT;
	    }
	    
	    ///////////////////////
	    // frequency 1 maz
	    ///////////////////////    
	     else if( !strcmp(str,"max_w2") ) 
	    {
		  fscanf(f,"%f",&FLT);		  
		  sys->maxW2= FLT;
	    }
	    
	    ///////////////////////
	    // frequency 1 resolution
	    ///////////////////////    
	     else if( !strcmp(str,"nb_w2") )
	    {
		  fscanf(f,"%d",&INT);		  
		  sys->nW2= INT;
	    }
		   
	     ///////////////////////
	    // min time
	    ///////////////////////    
	     else if( !strcmp(str,"initial_time") ) 
	    {
		  fscanf(f,"%f",&FLT);		  
		  sys->t0= FS2UA*FLT;
	    }
	    
	    ///////////////////////
	    // frequency 1 maz
	    ///////////////////////    
	     else if( !strcmp(str,"max_time_(fs)") ) 
	    {
		  fscanf(f,"%f",&FLT);		  
		  sys->tmax= FS2UA*FLT;
	    }
	    
	    ///////////////////////
	    // frequency 1 resolution
	    ///////////////////////    
	     else if( !strcmp(str,"numb_of_time_step") )
	    {
		  fscanf(f,"%d",&INT);		  
		  sys->nDiv= INT;
	    }
	    
	    ///////////////////////
	    // Inhomogeneous broadening
	    ///////////////////////    
	     else if( !strcmp(str,"inhom_broadening") ||  !strcmp(str,"static_disorder") )
	    {
		  fscanf(f,"%f",&FLT);		  
		  sys->disorder_amp= FLT;
	    }
	    
	    ///////////////////////
	    // number of realisation
	    ///////////////////////    
	     else if( !strcmp(str,"nbr_real") )
	    {
		  fscanf(f,"%d",&INT);		  
		  sys->disorder_nReal= INT;
		  if(INT == 1)
		    sys->disorder_amp = 0.0;
	    }
	    
	    ///////////////////////
	    // esa
	    ///////////////////////    
	     else if( !strcmp(str,"ESA") )
	    {
		  fscanf(f,"%s",str2);		  
		  strcpy(sys->ESA,str2);
	    }
	    
	    //////////////////////
	    // ese
	    ///////////////////////    
	     else if( !strcmp(str,"ESE") )
	    {
		  fscanf(f,"%s",str2);		  
		  strcpy(sys->ESE,str2);
	    }
	    
	     ///////////////////////
	    // gsb
	    ///////////////////////    
	     else if( !strcmp(str,"GSB") )
	    {
		  fscanf(f,"%s",str2);		  
		  strcpy(sys->GSB,str2);
	    }
		   
    ////////////////////////////////
    //      default case
    ////////////////////////////////
		   
	  else
      printf(" ERROR: CORRUPTED MAIN INPUT FILE: %s is not a valid entry \n",str);
      //exit(1);
	  
	
      }

      
   }
   
   fclose(f);
}









///////////////////////////////////////////////////////////////////////////
//			PULSES_2D
////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////
	// 		read the first pulses
	////////////////////////////////////////////// 
	
	// type
// 	else if( !strcmp(str,"pulse_1_type")  	||
// 		 !strcmp(str,"PULSE_1_TYPE")	 )
// 	{  
// 	    fscanf( f, "%s", str3 );
// 	    strcpy(pulse->type1,str3);	  
// 	}
// 	   
// 	// ampliture   
// 	else if( !strcmp(str,"pulse_1_amp")  	||
// 		 !strcmp(str,"PULSE_1_AMP")	 )
// 	{  
// 	    fscanf( f, "%f", &FLT );
// 	    pulse->eps1 = FLT;	  
// 	}   
// 	
// 	//time of the max amp
// 	else if( !strcmp(str,"pulse_1_t0_(fs)")  	||
// 		 !strcmp(str,"PULSE_1_T0_(FS)")	 )
// 	{  
// 	    fscanf( f, "%f", &FLT );
// 	    pulse->t1 = FLT;	  
// 	} 	   
// 	   
// 	//width of the pulse
// 	else if( !strcmp(str,"pulse_1_width")  	||
// 		 !strcmp(str,"PULSE_1_WIDTH")	 )
// 	{  
// 	    fscanf( f, "%f", &FLT );
// 	    pulse->sigma1 = FLT;	  
// 	} 
// 	
// 	//frequency of the pulse
// 	else if( !strcmp(str,"pulse_1_freq")  	||
// 		 !strcmp(str,"PULSE_1_FREQ")	 )
// 	{  
// 	    fscanf( f, "%f", &FLT );
// 	    pulse->wL1 = FLT;	  
// 	}
// 	
// 	
// 	//////////////////////////////////////////////
// 	// 		read the second pulses
// 	////////////////////////////////////////////// 
// 	
// 	// type
// 	else if( !strcmp(str,"pulse_2_type")  	||
// 		 !strcmp(str,"PULSE_2_TYPE")	 )
// 	{  
// 	    fscanf( f, "%s", str3 );
// 	    strcpy(pulse->type2,str3);	  
// 	}
// 	   
// 	// ampliture   
// 	else if( !strcmp(str,"pulse_2_amp")  	||
// 		 !strcmp(str,"PULSE_2_AMP")	 )
// 	{  
// 	    fscanf( f, "%f", &FLT );
// 	    pulse->eps2 = FLT;	  
// 	}   
// 	
// 	//time of the max amp
// 	else if( !strcmp(str,"pulse_2_t0_(fs)")  	||
// 		 !strcmp(str,"PULSE_2_T0_(FS)")	 )
// 	{  
// 	    fscanf( f, "%f", &FLT );
// 	    pulse->t2 = FLT;	  
// 	} 	   
// 	   
// 	//width of the pulse
// 	else if( !strcmp(str,"pulse_2_width")  	||
// 		 !strcmp(str,"PULSE_2_WIDTH")	 )
// 	{  
// 	    fscanf( f, "%f", &FLT );
// 	    pulse->sigma2 = FLT;	  
// 	} 
// 	
// 	//frequency of the pulse
// 	else if( !strcmp(str,"pulse_2_freq")  	||
// 		 !strcmp(str,"PULSE_2_FREQ")	 )
// 	{  
// 	    fscanf( f, "%f", &FLT );
// 	    pulse->wL2 = FLT;	  
// 	}
// 	
// 	//////////////////////////////////////////////
// 	// 		read the third pulses
// 	////////////////////////////////////////////// 
// 	
// 	// type
// 	else if( !strcmp(str,"pulse_3_type")  	||
// 		 !strcmp(str,"PULSE_3_TYPE")	 )
// 	{  
// 	    fscanf( f, "%s", str3 );
// 	    strcpy(pulse->type3,str3);	  
// 	}
// 	   
// 	// ampliture   
// 	else if( !strcmp(str,"pulse_3_amp")  	||
// 		 !strcmp(str,"PULSE_3_AMP")	 )
// 	{  
// 	    fscanf( f, "%f", &FLT );
// 	    pulse->eps3 = FLT;	  
// 	}   
// 	
// 	//time of the max amp
// 	else if( !strcmp(str,"pulse_3_t0_(fs)")  	||
// 		 !strcmp(str,"PULSE_3_T0_(FS)")	 )
// 	{  
// 	    fscanf( f, "%f", &FLT );
// 	    pulse->t3 = FLT;	  
// 	} 	   
// 	   
// 	//width of the pulse
// 	else if( !strcmp(str,"pulse_3_width")  	||
// 		 !strcmp(str,"PULSE_3_WIDTH")	 )
// 	{  
// 	    fscanf( f, "%f", &FLT );
// 	    pulse->sigma3 = FLT;	  
// 	} 
// 	
// 	//frequency of the pulse
// 	else if( !strcmp(str,"pulse_3_freq")  	||
// 		 !strcmp(str,"PULSE_3_FREQ")	 )
// 	{  
// 	    fscanf( f, "%f", &FLT );
// 	    pulse->wL3 = FLT;	  
// 	}

