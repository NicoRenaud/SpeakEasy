
#ifndef _defMacro_H
#define _defMacro_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tgmath.h>
#include <time.h>
#include <cblas.h>


#include <gsl_sf_bessel.h>
#include <gsl_rng.h>
#include <gsl_randist.h>
#include <gsl_vector.h>
#include <gsl_multifit_nlin.h>


#define KB 8.67 * pow(10,-5) 
#define CAHRGE 1.602176468 * pow(10,-19)
#define HBAR 1.05 * pow(10,-34)
#define FS2UA 1.5192678
#define PI 3.14116457148 
#define DBG 0



////////////////////////////////////////////
// define the MPI utilisation or not
// 1 = MPI	0 = no MPI
////////////////////////////////////////////
#define _MPI_ 0






///////////////////////////////////////
// 	 STRUCTURES : SYSTEM
///////////////////////////////////////

typedef struct{
         
    // general info
    int nState;
     
    // time
    float t0;
    float tmax;
    int nDiv;
    
    // hamiltonien
    char hmltn_mat[20];
    char unit[20];
    
    // relaxation matrix
    char relax_mat[20];

    // dipole interaction grd to sgl
    char dipole_mat[20];
    
    // dipole interaction sgl to dbl
    char dipole_mat_2[20];
    
    // frequency domain
    float minW1, maxW1;
    int nW1;
    float minW2, maxW2;
    int nW2;
    
    // temeprature
    float temp;
    
    // relaxation to the ground statre
    float grd_relax;
    
    // relaxation inter simply excited
    float simply_relax;
    float simply_dephas;
    
    // relaxation from double to single
    float dbl2sglrelax;
    
    
    // grd2sgl dipole
    float grd2sgl_dipole;
    float grd2sgl_freq;
    float grd2sgl_width;
    
    // sgl2dbl dipole
    float sgl2dbl_dipole;
    float sgl2dbl_freq;
    float sgl2dbl_width;
    
    
    // static disorder aka inhomogeneous broadening
    float disorder_amp;
    int disorder_nReal;
    
    
    // component (debugg)
    char GSB[10];
    char ESE[10];
    char ESA[10];
     
} SYS;         

// Parameters of the system    



#endif
