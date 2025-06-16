/*====== Modules ===============
   Keys to switch on 
   various modules of micrOMEGAs  
================================*/

//...Calculate Freeze out relic density and display contribution of  individual channels
#define OMEGA        
//...Calculate relic density in Freeze-in scenario
#define FREEZEIN     
//...Calculate N dm relic density
#define NdmParticles 

//...Calculate amplitudes and cross-sections for CDM-nucleon scattering
#define CDM_NUCLEON  

/*===== end of Modules  ======*/

/*===== End of DEFINE  settings ===== */

#include"../include/micromegas.h"
#include"../include/micromegas_aux.h"
#include"lib/pmodel.h"

//=======================================================//
//=======================================================//
//=======================================================//
int main(int argc,char** argv)
{  int err;
   char cdmName[10];
   int spin2, charge3,cdim;
   int fast=0;
//=======================================//
//...Choice of gauge + 3-body f-states...//
//=======================================//
  ForceUG=0;             /* to force Unitary Gauge assign 1 */
  VZdecay=0; VWdecay=0;  /* WW* and ZZ* channels are on */

//======================================//
//...Change external parameter values...//
//======================================//
  assignValW("mss",  10.);
  assignValW("lamssh", 0.16);

//=============================================================//
//...Sort odd particle spectrum and identify DM candidate(s)...//
//=============================================================//
  err=sortOddParticles(cdmName);
  qNumbers(CDM[1], &spin2, &charge3, &cdim);

//===============================================//
//...Freeze-out scenario dark matter abundance...//
//===============================================//
#ifdef OMEGA
{ int fast=0;
  double Beps=1.E-4, cut=0.01;
  double Xf;
  double omegaFO;  
  int i,err; 

  printf("\n======================================================================\n");   
  printf("\n==== Calculation of relic density in thermal freeze-out scenario =====\n");   
  printf("\n======================================================================\n");
  printf("\n");

//...Compute the relic
  omegaFO=darkOmega(&Xf,fast,Beps,&err);

  printf("\n=============================\n");   
  printf("\n==== Freeze-out results =====\n");   
  printf("\n=============================\n");
  printf("\n");
  printf("Omega freeze-out=%.2e\n", omegaFO);
  printf("\n======================================================================\n");

//...Print leading channels
  printChannels(Xf,cut,Beps,1,stdout);

  printf("\n======================================================================\n");
}
#endif

//============================================//
//...WIMP-nucleon scattering cross-sections...//
//============================================//
//  #ifdef CDM_NUCLEON
//  { double pA0[2],pA5[2],nA0[2],nA5[2];
//    double Nmass=0.939; /*nucleon mass*/
//    double SCcoeff;        
//    double csSIp1,csSIn1,csSDp1,csSDn1, csSIp1_,csSIn1_,csSDp1_,csSDn1_;   
//  
//  //...Compute the amplitudes for proton/neutron spin-independent/spin-dependent scattering
//    nucleonAmplitudes(CDM[1], pA0,pA5,nA0,nA5);
//  
//  //...Compute the corresponding cross-sections
//    SCcoeff=4/M_PI*3.8937966E8*pow(Nmass*McdmN[1]/(Nmass+ McdmN[1]),2.);
//    csSIp1=  SCcoeff*pA0[0]*pA0[0];
//    csSDp1=3*SCcoeff*pA5[0]*pA5[0];
//    csSIn1=  SCcoeff*nA0[0]*nA0[0];
//    csSDn1=3*SCcoeff*nA5[0]*nA5[0];
//                    
//    printf("\n==== Calculation of %s-nucleon cross sections [pb]: ====\n",CDM[1]);
//    printf(" proton  SI %.3E SD %.3E \n", csSIp1,csSDp1);
//    printf(" neutron SI %.3E SD %.3E \n", csSIn1,csSDn1);     
//    printf("\n======================================================================\n");
//  }
//  #endif

//====================================================//
//...Redefine coupling, more suitable for freeze-in...//
//====================================================//
//    assignValW("lamssh", 1.995e-12);
//    
//    err=sortOddParticles(cdmName);
//    qNumbers(CDM[1], &spin2, &charge3, &cdim);

//==============================================//
//...Freeze-in scenario dark matter abundance...//
//==============================================//
//  #ifdef FREEZEIN
//  {
//    double TR=1E5;
//    double omegaFI, omegaFIdec;  
//  
//  //...Add the lightest odd particle to the list of feeble particles
//    toFeebleList(CDM[1]);
//    
//    printf("\n=============================================================\n");   
//    printf("\n==== Calculation of relic density in freeze-in scenario =====\n");   
//    printf("\n=============================================================\n");
//    printf("\n");
//  
//  
//  //...Full calculation
//    omegaFI=darkOmegaFi(TR,CDM[1],&err);
//  
//  //...Calculation based on Higgs decays only  
//    omegaFIdec = darkOmegaFiDecay(TR, "H", "~ss");
//  
//    printf("\n============================\n");   
//    printf("\n==== Freeze-in results =====\n");   
//    printf("\n============================\n");
//    printf("\n");
//    printf("omega freeze-in=%.3E\n", omegaFI);
//    printf("omega freeze-in from Higgs decays=%.3E\n", omegaFIdec);
//    printf("\n======================================================================\n");
//  
//  //...Print leading channels
//    printChannelsFi(0,0,stdout);//...Full calculation
//  
//  
//  //...Always a good idea to empty the list of feeble particles after the computation
//    toFeebleList(NULL);
//  }
//  #endif

//=================================================================//
//...Computation using "full" Boltzmann equation and comparisons...//
//=================================================================//
//  #ifdef NdmParticles
//  { 
//    double Beps=1.E-4, cut=0.01;
//    double omegaFOfo, omegaFIfo, omegaFullfo;
//    double omegaFOfi, omegaFIfi, omegaFullfi;
//    double omegaFOintermediate, omegaFIintermediate, omegaFullintermediate;
//    double Xf;
//    int i,err; 
//    double Y[1];
//    
//  
//    printf("\n=======================================\n");   
//    printf("\n==== From freeze-in to freeze-out =====\n");   
//    printf("\n=======================================\n");
//    printf("\n");
//  
//  //...................................................//
//  //...................................................//
//  //...Scenario 1: Freeze-out
//    double TR=1E4;
//    assignValW("lamssh", 0.16);
//    
//    err=sortOddParticles(cdmName);
//    qNumbers(CDM[1], &spin2, &charge3, &cdim);
//  
//  //...Freeze-out (for comparison)
//    cleanDecayTable();
//    omegaFOfo=darkOmega(&Xf,fast,Beps,&err);
//  
//  //...Freeze-in (for comparison)
//    cleanDecayTable();
//    toFeebleList(CDM[1]);
//    omegaFIfo=darkOmegaFi(TR,CDM[1],&err);
//    toFeebleList(NULL);
//  
//  //...Full calculation
//  //...Set the initial DM abundance to zero
//    Y[0]=0.;
//  
//  //...Compute the relic density                    
//    cleanDecayTable();
//    omegaFullfo = darkOmegaTR(TR,Y[0],fast,Beps,&err);   
//  
//  //...................................................//
//  //...................................................//
//  //...Scenario 2: Freeze-in
//    TR=1E4;
//    assignValW("lamssh", 1.995e-12);
//    
//    err=sortOddParticles(cdmName);
//    qNumbers(CDM[1], &spin2, &charge3, &cdim);
//  
//  //...Freeze-out (for comparison)
//    cleanDecayTable();
//    omegaFOfi=darkOmega(&Xf,fast,Beps,&err);
//  
//  //...Freeze-in (for comparison)
//    cleanDecayTable();
//    toFeebleList(CDM[1]);
//    omegaFIfi=darkOmegaFi(TR,CDM[1],&err);
//    toFeebleList(NULL);
//  
//  //...Full calculation
//  //...Set the initial DM abundance to zero
//    Y[0]=0.;
//  
//  //...Compute the relic density                    
//    cleanDecayTable();
//    omegaFullfi = darkOmegaTR(TR,Y[0],fast,Beps,&err);   
//  
//  //...................................................//
//  //...................................................//
//  //...Scenario 3: Freeze-in with backreactions
//    TR=1E0;
//    assignValW("mss", 20.35);
//    assignValW("lamssh", 0.11);
//    
//    err=sortOddParticles(cdmName);
//    qNumbers(CDM[1], &spin2, &charge3, &cdim);
//  
//  //...Freeze-out (for comparison)
//    cleanDecayTable();
//    omegaFOintermediate=darkOmega(&Xf,fast,Beps,&err);
//  
//  //...Freeze-in (for comparison)
//    cleanDecayTable();
//    toFeebleList(CDM[1]);
//    omegaFIintermediate=darkOmegaFi(TR,CDM[1],&err);
//    toFeebleList(NULL);
//  
//  //...Full calculation
//  //...Set the initial DM abundance to zero
//    Y[0]=0.;
//  
//  //...Compute the relic density                    
//    cleanDecayTable();
//    omegaFullintermediate = darkOmegaTR(TR,Y[0],fast,Beps,&err);   
//  //...................................................//
//  //...................................................//
//  
//    printf("\n==================\n");   
//    printf("\n==== Results =====\n");   
//    printf("\n==================\n");
//    printf("\n");
//  
//    printf("\n======================================================================\n");
//  
//    printf("Scenario 1: freeze-out benchmark\n");
//    printf("omega freeze-out=%.3E\n", omegaFOfo);
//    printf("omega freeze-in=%.3E\n", omegaFIfo);
//    printf("omega full=%.3E\n", omegaFullfo);
//    printf("\n======================================================================\n");
//  
//    printf("Scenario 1: freeze-in benchmark\n");
//    printf("omega freeze-out=%.3E\n", omegaFOfi);
//    printf("omega freeze-in=%.3E\n", omegaFIfi);
//    printf("omega full=%.3E\n", omegaFullfi);
//    printf("\n======================================================================\n");
//  
//    printf("Scenario 1: intermediate benchmark\n");
//    printf("omega freeze-out=%.3E\n", omegaFOintermediate);
//    printf("omega freeze-in=%.3E\n", omegaFIintermediate);
//    printf("omega full=%.3E\n", omegaFullintermediate);
//  
//    printf("\n======================================================================\n");
//  
//  }
//  #endif

  return 0;
}












