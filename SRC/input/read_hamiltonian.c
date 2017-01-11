#include "../defMacro.h"






/////////////////////////////////////////////
//       Read the operators  form files    //
/////////////////////////////////////////////

void read_mat(float *MAT, int n1,int n2, char *file_name, char *SYM)
{

	int nInd;
     	float FLT;
     	FILE *f;
	char *pch;
     	char trash[100];
	char str[100];
	char str_cmt[3];
	int index1,index2;

     	// ouverture du fichier
     	f = fopen(file_name,"r");

	// brak in case of a problem
     	if (!f) 
	{
        	printf("couldn't read %s\n", file_name);
        	exit(1);
      	}
	// otherwize reading
      	while(!feof(f))
	{		
	  
		
			// read the first string
			fscanf(f,"%s",trash);

			
// 		        ////////////////////////
// 			// if it's a comment
// 			////////////////////////
			
			strncpy(str_cmt,trash,2);
			str_cmt[2] = '\0';
			
			// then  read the line
			if (!strcmp(str_cmt,"//"))
			  fgets(str,99,f);
			
			
// 		        ////////////////////////
// 			// if it's not a comment
// 			////////////////////////
			else
			{
			  
			  // cptr
			  nInd = 0;
			  
			  // decoupe trash en  segment
			  strcpy(str,trash);
			  pch = strtok (str,"[]");
			  
			  // keep cutting
			  while (pch != NULL)
			  {
			    
			    pch = strtok (NULL, "[]");
			    
			    // choose which index
			    if(nInd == 0)
			      index1 = (int) atoi(pch);
			    if(nInd == 1)
			      index2 = (int) atoi(pch);
			    
			    // increment index
			    nInd ++;
			    
			  }
			  
			  
			  // read the value
			  fscanf(f,"%f",&FLT);

			  // put in tje matrix
			  MAT[(index1-1)*n2+index2-1] = FLT;

			  
			  if(!strcmp(SYM,"sym"))
			  {
			    if(index1!=index2)
				  MAT[(index2-1)*n1+index1-1] = FLT;
			  }
			}
			
			

        }
        
        fclose(f);
         
}


/////////////////////////////////////////////
//       Read Relaxation Matrix		   //
/////////////////////////////////////////////
void read_Rs(float *MAT,float *Us, int n1, int n2, char *file_name)
{
  
    int nInd;
    float FLT;
    FILE *f;
    char trash[100];
    char *pch;
    char str[100];
    char str_cmt[3];
    char BASIS[6];
    int index1,index2;


    // ouverture du fichier
    f = fopen(file_name,"r");
    
    // brak in case of a problem
    if (!f) 
    {
	    printf("couldn't read %s\n", file_name);
	    exit(1);
    }
    // otherwize reading
    while(!feof(f))
    {		    
       
	  fscanf(f,"%s",trash);
      
          ////////////////////////
	  // if it's a comment
	  ////////////////////////
	  strncpy(str_cmt,trash,2);
	  str_cmt[2] = '\0';
			
	 if (!strcmp(str_cmt,"//"))
	      fgets(str,99,f);
	 
	 else if (!strcmp(trash,"basis") || !strcmp(trash,"BASIS") )
	   fscanf(f,"%s",BASIS);
	   
	  ////////////////////////
	  // if it's not a comment
	  ////////////////////////
	  else
	  {
	    
	    // cptr
	    nInd = 0;
	    
	    // decoupe trash en  segment
	    strcpy(str,trash);
	    pch = strtok (str,"[]");
	    
	    // keep cutting
	    while (pch != NULL)
	    {
	      
	      pch = strtok (NULL, "[]");
	      
	      // choose which index
	      if(nInd == 0)
		index1 = (int) atoi(pch);
	      if(nInd == 1)
		index2 = (int) atoi(pch);
	      
	      // increment index
	      nInd ++;
	      
	    }
	    
	    
	    // read the value
	    fscanf(f,"%f",&FLT);

	    // put in tje matrix
	    MAT[(index1-1)*n1+index2-1] = FLT;
	    if(index1!=index2)
		    MAT[(index2-1)*n2+index1-1] = FLT;
	  }
	

    }

    
    // rotation of Rs
    if(!strcmp(BASIS,"EIGEN") || !strcmp(BASIS,"eigen"))
      real_eigen2local(MAT, Us, n1);
    else if(!strcmp(BASIS,"LOCAL") || !strcmp(BASIS,"local"))
    {	}
    else
    {
      printf("Warning : basis set %s not recognized importing the matrix %s",BASIS,file_name);
      printf("          eigen basis set used by default\n");
    }
    
}


