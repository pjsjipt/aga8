// Programa para interfaceamento do programa de cálculo de compressibilidade

#include <stdio.h>

// Funções de interface:

#include "aga8_gross.h"


Aga8_gross gross;		// Variável para fazer os cálculos


extern "C"{
  
  void setparams_(double *xread, double *ZB, double *DB, double *MWeight, int *cod);
  //      subroutine fastcalc(TT, PP, Z,ZB,  Fpv, Rho, codigo)
  void fastcalc_(double *TT, double *PP, double *Z, double *ZB, double *Fpv, 
		 double *Rho, int *cod);

  int maximo(int *nn, int N){
    // Esta função acha o mãximo de um vetor:
    int i;
    int nmax = nn[0];
    for (i = 0; i < N; i++)
      if (nn[i] > nmax) nmax = nn[i];
    
    return nmax;
  }


  void R_setcomp(double *x, double *ZB, double *MW){

    double DB;
    int cod;
    setparams_(x, ZB, &DB, MW, &cod);
    return;
  }

  void R_aga8_detail(double *TT, double *PP, double *Z, int *nn){
    int i, N, cod;
    double T, P, ZB, Fpv, Rho;
    
    N = maximo(nn, 2);
    for(i = 0; i < N; i++){
      // Para cada pressão e temperatura, calcular
      // a compressibilidade. Lembrar das ´recycling rules´
      T = TT[i % nn[0]];
      P = PP[i % nn[1]];
      fastcalc_(&T, &P, &Z[i], &ZB, &Fpv, &Rho, &cod);
    }
  }
  int teste(){
    
    double xread[21]; 
    double ZB = 1.0, DB = 1.0, MW, Z, TT, PP;
    int cod, i, nn[2];
    nn[0] = 1;
    nn[1] = 1;
    TT = 20.0;
    PP = 0.101325;
    
    for (i = 0; i < 21; i++)
      xread[i] = 0.0;
    xread[0] = 1.0;
    
    setparams_(xread, &ZB, &DB, &MW, &cod);
    R_aga8_detail(&TT, &PP, &Z, nn); 
    printf("MW = %lf ZB=%lf DB=%lf \n", MW, ZB, DB);
    printf("Z = %lf\n", Z);
  }

  


  // Interface para o gross

  void R_set_grossA(double *x_CO2, double *x_H2, double *d, double *Hs,
		   double *x_CO){
    gross.set_A(*Hs, *d, *x_CO2, *x_H2, *x_CO);
  }

  void R_set_grossB(double *x_CO2, double *x_H2, double *d, double *x_N2,
		   double *x_CO){
    gross.set_B(*d,*x_N2, *x_CO2, *x_H2, *x_CO);
  }

  void R_get_MW(double *mw){
    // Esta função retorna os dados de massa molecular 
    *mw = gross.MW;
  }


  void R_conc_gross(double *N2, double *CO2, double *H2, double *CO){

    gross.concentration(N2, CO2, H2, CO);
  }
  
  
  void R_aga8_gross(double *TT, double *PP, double *Z, int *nn){
    int i, N, cod;
    double T, P, ZB, Fpv, rho, rhom;
    
    N = maximo(nn, 2);
    for(i = 0; i < N; i++){
      // Para cada pressão e temperatura, calcular
      // a compressibilidade. Lembrar das ´recycling rules´
      T = TT[i % nn[0]];
      P = PP[i % nn[1]];
      gross.calc(P, T, Z[i], rhom, rho);
    }
  }



  void R_aga8_gross_rho(double *TT, double *PP, double *rho, int *nn){
    int i, N, cod;
    double T, P, ZB, Fpv, Z, rhom;
    
    N = maximo(nn, 2);
    for(i = 0; i < N; i++){
      // Para cada pressão e temperatura, calcular
      // a compressibilidade. Lembrar das ´recycling rules´
      T = TT[i % nn[0]];
      P = PP[i % nn[1]];
      gross.calc(P, T, Z, rhom, rho[i]);
    }
  }

  void R_BVirial(double *TT, double *B, int *nn){
    int i, N;
    double T;

    N = *nn;
    for (i = 0; i < N; ++i){
      T = TT[i] + 273.15;
      B[i] = gross.BVIRIAL(T);
    }
  }

  void R_CVirial(double *TT, double *C, int *nn){
    int i, N;
    double T;

    N = *nn;
    for (i = 0; i < N; ++i){
      T = TT[i] + 273.15;
      C[i] = gross.CVIRIAL(T);
    }
  }
  
    
      
	
}

	
