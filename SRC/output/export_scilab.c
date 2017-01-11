#include "../defMacro.h"




void export_scilab(complex float *S, float *W1, int nw1, float *W2, int nw2, float *T, int iT, char *file_name)
{
  
  char file_tot[250];
  char nbr[250];
  FILE *f;
  int i,j,k=0;
  float ratio=1.0;
  
  /*
  if(!strcmp(unit,"WN"))
    ratio = 8065.541154;
  else
    ratio = 1.;
  */
  
  // determine the complete file name
  strcpy(file_tot,file_name);

  sprintf(nbr,"%d",iT);
  strcat(file_tot,nbr);
  strcat(file_tot,".sci");
  

  // open the file
  f = fopen(file_tot,"w");
  
  // check it's ok
  if (!f) 
  {
      printf("couldn't read %s in export scilab\n",file_tot);
      exit(1);
  }
  
  // print the data
  else
  {
    
    fprintf(f,"T=%f;\n",T[iT]/FS2UA);
    fprintf(f,"S = [];\n");
     for(i=0;i<nw1;i++)
      {
	  for(j=0;j<nw2;j++)
	  {
	    fprintf(f,"S(%d,%d)= %f+%%i*%f;\n",i+1,j+1,crealf(S[k]),cimagf(S[k]));
	    k++;
	  }
	 
      }

      fprintf(f,"W1 = [\n");
      for(i=0;i<nw1;i++)
        fprintf(f,"%f,..\n",ratio*W1[i]);
      fprintf(f,"];\n");
      
      fprintf(f,"W2 = [\n");
      for(i=0;i<nw2;i++)
        fprintf(f,"%f,..\n",ratio*W2[i]);
      fprintf(f,"];\n");
    
  }
  
  // close the file
  fclose(f);
 
}