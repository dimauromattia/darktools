#include<math.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include <dlfcn.h>
#include <sys/wait.h> 
#include"num_in.h"
#include"num_out.h"
#include"VandP.h"
#include"dynamic_cs.h"
#include"rootDir.h" 
#include <time.h>

int main(void)
{ int err,i;

	/* INTPUT PARAMETERS (to scan over) */

	/* OUTPUT PARAMETERS */
    // Higgs decay branching ratios
    double  wh,braa;
txtList branchings_MP,branchings_HD,branchings_tp,branchings_V0;

//set model dir here
char mdldir[] = "/home/belyaev/Downloads/DarkTools/FPVDM";

 // Set model number and number of points to collect, mdlnr is your model number
int mdlnr=1;

//a model to switch between to reset values when reloading
 setModel(mdldir , mdlnr ); 

/*****************************************************************************/
 srand (time(NULL)); //this is used to seed the random number by the system time

 if (remove("scan2.dat") == -1)
	perror("Error in deleting a file");

 FILE *file;
 file = fopen("scan2.dat","a+"); /* apend file (add text to
					a file or create a file if it does not exist.*/

 // Writing parameter names at first line to keep track of columns:
 //input parameters (1)
 //output parameters (3)
 fprintf(file,"MHD\t\t Br(Tp->V' t) \t Br(Tp->HD t)\t  Br(HD->t,T) \t  Br(V'->t,T)\n");		
 fclose(file); /*done with header of file*/

 /*** Starting randomizing loop ***/
int npoints=50;
double wTP,wHD,wV0,BrTP__Vp_t,BrTP__HD_t,BrHD__t_t,BrVp__t_t;
double Mtp=1100,MtD=900,MV=500,gd=0.1;
 for (i = 0; i <= npoints; i++){

 /********** generate random values for variables **********/
 /*Mh     = Mhmin+(double) random()/RAND_MAX*(Mhmax-Mhmin);*/
 double MHD,LogMHDmin=0,LogMHDmax=4;
 
 MHD  = pow(10,(LogMHDmin+ i*(LogMHDmax-LogMHDmin)/npoints));

 /* Have to reset model every time, otherwise widths are not recalculated */
 setModel(mdldir , mdlnr ); 

 /******* assign variable values ********/
 /* the string is the calchep var name */
  err=assignValW("MtD", MtD);
  err=assignValW("Mtp", Mtp);
  err=assignValW("Mh2", MHD);
  err=assignValW("MV",  MV);
  err=assignValW("gd",  gd);

 // Calculation of public constraints  
 err=calcMainFunc();

 if(err!=0) { 
	  printf("Can not calculate constrained parameter %s\n",varNames[err]);i--;
 }
 else {
		// if the point survives the constraints collect more output values:
		// width and branchings of a particle
		wTP    = pWidth("tp",&branchings_tp);
		wHD    = pWidth("h2",&branchings_HD);
		wV0    = pWidth("V0",&branchings_V0);
		
		BrTP__Vp_t= findBr(branchings_tp,"V0,t");
		BrTP__HD_t= findBr(branchings_tp,"HD,t");
		BrHD__t_t=  findBr(branchings_HD,"T,t");
		BrVp__t_t=  findBr(branchings_V0,"T,t");
	
		// write values to file
  		file  = fopen("scan2.dat","a+");
		//input parameters
  		fprintf(file,"%f\t",MHD);
		//output parameters
  		fprintf(file,"%e\t%e\t%e\t%e\n",BrTP__Vp_t, BrTP__HD_t,BrHD__t_t,BrVp__t_t);
  		fclose(file); 
 }
  
 }// *** end of rand loop ***

  return 0;
}

