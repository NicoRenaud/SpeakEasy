#include "../defMacro.h"

void export_gnuplot(complex float *S, float *W1, int nw1, float *W2, int nw2, float *T, int iT, char *file_name)
{
  
  char file_real[250];
  char file_imag[250];
  char file_mod[250];
  char nbr[250];
  FILE *freal,*fimag,*fmod;
  int i,j,k=0;
  float ratio=1.0;
  float x;
  float eps = powf(1.0,-10);
  
  // determine the complete file name
  strcpy(file_real,file_name);
  strcat(file_real,"real_");
  
  strcpy(file_imag,file_name);
  strcat(file_imag,"imag_");
  
  strcpy(file_mod,file_name);
  strcat(file_mod,"mod_");
  
  // number of the file
  sprintf(nbr,"%d",iT);
  strcat(file_real,nbr);
  strcat(file_real,".dat");
  
  strcat(file_imag,nbr);
  strcat(file_imag,".dat");
  
  strcat(file_mod,nbr);
  strcat(file_mod,".dat");
  
  // open the files
  freal = fopen(file_real,"w");
  fimag = fopen(file_imag,"w");
  fmod = fopen(file_mod,"w");
  printf("%s\n",file_real);
  
  // check it's ok
  if (!freal)
  {
    printf("couldn't create %s in export_gnuplot()\n",file_real);
    exit(1);
  }
  
  // print the data
  else
  {
    
    for(i=0;i<nw1;i++)
    {
      for(j=0;j<nw2;j++)
      {
        x = crealf(S[k]);
        //x = log(x+sqrt(1+x*x)+eps);
        fprintf(freal,"%f %f %f\n",W1[i],W2[j],x);
                
        x = cimagf(S[k]);
        //x = log(x+sqrt(1+x*x)+eps);
        fprintf(fimag,"%f %f %f\n",W1[i],W2[j],x);
                
        x = S[k]*conj(S[k]);
        x = log(x+sqrt(1+x*x)+eps);
        fprintf(fmod,"%f %f %f\n",W1[i],W2[j],x);
        k++;
      }
      fprintf(freal,"\n");
      fprintf(fimag,"\n");
      fprintf(fmod,"\n");
    }
    
  }
  
  // close the file
  fclose(freal);
  fclose(fimag);
  fclose(fmod);
  
}