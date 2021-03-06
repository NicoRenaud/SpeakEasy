
#include "../defMacro.h"


/////////////////////////////////////////////////////////
//               Conversion cm-1 2 ev                  //
/////////////////////////////////////////////////////////


///////////////////////////////////////
//		matrix		     //
///////////////////////////////////////
void wn2ev(float *M, int size)
{
  
  int i;
  float ratio = 8065.541154;
  
  for(i=0;i<size;i++)
    M[i] = M[i]/ratio;

}

///////////////////////////////////////
//		matrix		     //
///////////////////////////////////////
void wn2ev_sys(SYS *sys)
{
  
  int i;
  float ratio = 8065.541154;
  
  sys->grd_relax /=ratio;
  sys->dbl2sglrelax /=ratio;
  sys->simply_dephas /=ratio;
  sys->simply_relax /=ratio;
  sys->grd2sgl_freq /=ratio;
  sys->grd2sgl_width /=ratio;
  sys->disorder_amp /= ratio;
}

