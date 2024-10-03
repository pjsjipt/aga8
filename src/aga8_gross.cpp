/** \file \brief Este arquivo implementa a classe Aga8_gross

Implementa os métodos da classe Aga8_gross, especificado no arquivo aga8_gross.h

*/
#include <cmath>
#include "aga8_gross.h"

using namespace std;

/**
   Esta função calcula o primeiro coeficiente virial da mistura. Utiliza a equação
   B.12 da ISO 12213-3.

   \param T Temperatura em K do gás
   \return O coeficiente virial B em m^3/kmol
 */
double Aga8_gross::BVIRIAL(double T)
{
  double x1, x2, x3, x4, x5;
  double B11, B12, B13, B14, B15, B22, B23, B24, B33, B44, B55;
  double temp;

  x1 = x_CH; x2 = x_N2; x3 = x_CO2; x4 = x_H2; x5 = x_CO;

 
  B11 =  -4.25468E-1 + 2.865E-3*T - 4.62073E-6*T*T +
    (    8.77118E-4 - 5.56281E-6*T + 8.81510E-9*T*T) * H_CH +
    (    -8.24747E-7 + 4.31436E-9*T - 6.08319E-12*T*T)*H_CH*H_CH;  // Eq. B.20
  
  B14 = -5.21280E-2 + 2.71570E-4*T - 2.5E-7*T*T; // Eq. B.22
  B15 = -6.8729E-2  - 2.39381E-6*T + 5.18195E-7*T*T;
  B22 = -1.446E-1 + 7.4091E-4*T - 9.11950E-7*T*T;
  B23 = -3.39693E-1 + 1.61176E-3*T - 2.04429E-6*T*T;
  B24 = 1.2E-2;
  B33 = -8.6834E-1 + 4.03760E-3*T - 5.16570E-6*T*T;
  B44 = -1.10596E-3 + 8.13385E-5*T -9.8722E-8*T*T;
  B55 = -1.30820E-1 + 6.02540E-4*T - 6.44300E-7*T*T;
  B12 = ( 0.72 + 1.875E-5*(320.0-T)*(320-T)) * (B11 + B22)/2.0;	// Eq. B.23
  B13 = -0.865 * sqrt(B11*B33);	// Eq. B.24

  temp = x1*x1*B11 + 2*x1*x2*B12 + 2*x1*x3*B13 + 2*x1*x4*B14 +
    2*x1*x5*B15 + x2*x2*B22 + 2*x2*x3*B23 + 2*x2*x4*B24 + x3*x3*B33 +
    x4*x4*B44 + x5*x5*B55;	// Eq. B.12

  return temp;
}


/**
   Calcula o segundo coeficiente virial da mistura para diferentes temperaturas

   \param T Temperatura em K
   \return Segundo coeficiente virial em m^6 / kmol^2

 */
double Aga8_gross::CVIRIAL(double T)
{
  // Calcula o coeficiente virial C a aprtira da composiçãop e temperatura

  double x1, x2, x3, x4, x5;
  double C111, C112, C113, C114, C115, C122, C123,
    C133, C222, C223, C233, C333, C444;
  
  double temp;

  x1 = x_CH; x2 = x_N2; x3 = x_CO2; x4 = x_H2; x5 = x_CO;

  C111 = -3.02488E-1 + 1.95861E-3*T - 3.16302E-6*T*T +
    (     6.46422E-4 - 4.22876E-6*T + 6.88157E-9*T*T) * H_CH +
    (    -3.32805E-7 + 2.23160E-9*T -3.67713E-12*T*T) * H_CH*H_CH; // Eq. B.29

  C222 = 7.84980E-3 - 3.98950E-5*T + 6.11870E-8*T*T; // Eq. B.31
  C333 = 2.05130E-3 + 3.48880E-5*T - 8.37030E-8*T*T;
  C444 = 1.04711E-3 - 3.64887E-6*T + 4.67095E-9*T*T;
  C115 = -7.36748E-3 - 2.76578E-5*T + 3.43051E-8*T*T;
  C223 = 5.52066E-3 - 1.68609E-5*T + 1.57169E-8*T*T;
  C233 = 3.58783E-3 + 8.06674E-6*T - 3.25798E-8*T*T;

  C112 = (0.92 + 0.0013*(T-270.0)) * pow(C111*C111*C222, 0.333333);//Eq. B.33
  C122 = (0.92 + 0.0013*(T-270.0)) * pow(C111*C222*C222, 0.333333);// Eq. B.33
  C113 = 0.92 * pow(C111*C111*C333, 0.33333); // Eq. B.34
  C133 = 0.92 * pow(C111*C333*C333, 0.33333); // Eq. B.34
  C114 = 1.2 * pow(C111*C111*C444, 0.333333); // Eq. B.35

  C123 = 1.1 * pow(C111*C222*C333, 0.333333); // Eq. B.36
  
  

  temp = x1*x1*x1*C111 + 3*x1*x1*x2*C112 + 3*x1*x1*x3*C113 + 3*x1*x1*x4*C114
    + 3*x1*x1*x5*C115 + 3*x1*x2*x2*C122 + 6*x1*x2*x3*C123
    + 3*x1*x3*x3*C133 + x2*x2*x2*C222 +
    3*x2*x2*x3*C223 + 3*x2*x3*x3*C233 + x3*x3*x3*C333 + x4*x4*x4*C444; // Eq. B.28

  return temp;
  
  
}

/**
   Método para especificação dos dados de entrada. Neste caso, os dados de entrada são:
   \param dd Densidade relativa - Densidade relativa nas condições normais
 */
void Aga8_gross::set_B(double dd, double xx_N2, double xx_CO2, double xx_H2,
		       double xx_CO)
{

  int u, v;
  double rho_D, DH, Hs_novo;
  // Conjunto de dados de entrada A

  d = dd; x_CO2 = xx_CO2; x_H2 = xx_H2;

  x_N2 = xx_N2;
  x_CO = xx_CO;

  x_CH = 1.0 - x_N2 - x_CO2 - x_H2 - x_CO;
  

  

  //if (xx_CO < 0.0) x_CO =  0.0964 * x_H2;
  
  
  // Calcular todos os parâmetros nas condições normais
  rho_n = d * rho_air;

  // Chutes iniciais para as iterações:
  H_CH = 1000.0;
  Bn = -0.065;


  rho_mn = 1 / (V_mn_id + Bn);

  v = 0;
  do {
    u = 0;
    do {
      u++;
      
      M_CH = calc_M_CH(H_CH);	// Calcular a massa molecular de CH

      // Calcular a fração molar de CH a partir do calor específico.
      
      Hs = (x_CH*H_CH + x_H2*H_H2 + x_CO*H_CO) * rho_mn;
      

      // Calcular o valor de rho_n
      rho_n_calc = ( x_CH*M_CH + x_N2*M_N2 + x_CO2*M_CO2 + x_H2*M_H2 + x_CO*M_CO) * rho_mn;

      // Verificar se houve convergência:

      if (fabs(rho_n - rho_n_calc) < EPS) break;

      // Verificar se já não passou dos limites para convergência:
      if (u > MAXITER)
	{
	  ERROR_FLAG = 1;
	  return;
	}

      // Não convergiu ainda, calcular novamente o rho
      rho_D = calc_rho(H_CH + 1.0);
      DH = (rho_n - rho_n_calc) / (rho_D - rho_n_calc);
      H_CH += DH;
      
      

    } while (1);

    // Incrementar contador v
    v++;

    // Calcular Bn
    Bn = BVIRIAL(Tn);

    // Recalcular rho_mn:
    rho_mn = 1 / (V_mn_id + Bn);
     
    // Calcular o o poder calorífico superior:
    Hs_novo = ( x_CH * H_CH + x_H2 * H_H2 + x_CO * H_CO ) * rho_mn;

    if ( fabs(Hs - Hs_novo) < 1e-4) break;

    // Verificar se passou o número máximo de iterações:
    if (v > MAXITER)
      {
	ERROR_FLAG = 2;
	return;
      }
    
  } while (1);

  // Desta maneira, esperamos ter todos os parâmetros calculados...
  // Calcular a massa molecular
  MW = x_CH*M_CH + x_N2*M_N2 + x_CO2*M_CO2 + x_H2*M_H2 + x_CO*M_CO;
  
}
  



    
  

void Aga8_gross::set_A(double HHs, double dd, double xx_CO2, double xx_H2,
		       double xx_CO)
{

  int u, v;
  double rho_D, DH, Hs_novo;
  // Conjunto de dados de entrada A

  Hs = HHs; d = dd; x_CO2 = xx_CO2; x_H2 = xx_H2;


  x_CO = xx_CO;

  //if (xx_CO == 0.0) x_CO =  0.0964 * x_H2;
  
  
  // Calcular todos os parâmetros nas condições normais
  rho_n = d * rho_air;  	// Eq. B.1

  // Chutes iniciais para as iterações:
  H_CH = 1000.0;                // Eq. na seção B.2.1
  Bn = -0.065;  		// Eq. na seção B.2.1


  rho_mn = 1 / (V_mn_id + Bn);	// Eq. B.4

  v = 0;
  do {
    u = 0;
    do {
      u++;
      
      M_CH = calc_M_CH(H_CH);	// Calcular a massa molecular de CH, eq. B.5

      // Calcular a fração molar de CH a partir do calor específico.
      x_CH = Hs / (H_CH * rho_mn) - (x_H2 * H_H2 + x_CO * H_CO) / H_CH;  // Eq. B.6
      x_N2 = 1 - x_CH - x_CO2 - x_H2 - x_CO; // Eq. B.7

      // Calcular o valor de rho_n, eq. B.8
      rho_n_calc = ( x_CH*M_CH + x_N2*M_N2 + x_CO2*M_CO2 + x_H2*M_H2 + x_CO*M_CO) * rho_mn; 

      // Verificar se houve convergência:

      if (fabs(rho_n - rho_n_calc) < EPS) break; // Eq. B.9

      // Verificar se já não passou dos limites para convergência:
      if (u > MAXITER)
	{
	  ERROR_FLAG = 1;
	  return;
	}

      // Não convergiu ainda, calcular novamente o rho
      // Fazer a operação B.4 - B.8 para Hch+1
      rho_D = calc_rho(H_CH + 1.0);

      DH = (rho_n - rho_n_calc) / (rho_D - rho_n_calc); // Eq. B.11
      H_CH += DH;
      
      

    } while (1);

    // Incrementar contador v
    v++;

    // Calcular Bn
    Bn = BVIRIAL(Tn);

    // Recalcular rho_mn:
    rho_mn = 1 / (V_mn_id + Bn);
     
    // Calcular o o poder calorífico superior:
    Hs_novo = ( x_CH * H_CH + x_H2 * H_H2 + x_CO * H_CO ) * rho_mn;

    if ( fabs(Hs - Hs_novo) < 1e-4) break;

    // Verificar se passou o número máximo de iterações:
    if (v > MAXITER)
      {
	ERROR_FLAG = 2;
	return;
      }
    
  } while (1);

  // Desta maneira, esperamos ter todos os parâmetros calculados...
  // Calcular a massa molecular
  MW = x_CH*M_CH + x_N2*M_N2 + x_CO2*M_CO2 + x_H2*M_H2 + x_CO*M_CO;
  
}
  

double Aga8_gross::calc_rho(double H)
{

  double GM1, xx_CH, xx_N2;

  GM1 = calc_M_CH(H);	// Calcular a massa molecular de CH

  // Calcular a fração molar de CH a partir do calor específico.
  xx_CH = Hs / (H * rho_mn) - (x_H2 * H_H2 + x_CO * H_CO) / H;
  xx_N2 = 1 - xx_CH - x_CO2 - x_H2 - x_CO;

  // Calcular o valor de rho_n
  return ( xx_CH*GM1 + xx_N2*M_N2 + x_CO2*M_CO2 + x_H2*M_H2 + x_CO*M_CO) * rho_mn;
}
  

void Aga8_gross::concentration(double *N2, double *CO2, double *H2, double *CO){

  *N2 = x_N2;
  *CO2 = x_CO2;
  *H2 = x_H2;
  *CO = x_CO;
}


    

void Aga8_gross::calc(double P, double t, double &Z, double &rhom, double &rho)
{

  // Esta subrotina é a principal rotina de cálculo de compressibilidade
  int w = 0;
  double T = t + 273.15;
  double C, B, p_novo;
  
  // calcular os coeficientes viriais:
  B = BVIRIAL(T); 
  C = CVIRIAL(T);

  // Chute inicial:
  rhom =  P/(R*T);    //1 / ( R*T/P + B);
  p_novo = P;
  do {
    ++w;

    p_novo = p_novo + (R*T*rhom * (1 + B*rhom + C*rhom*rhom) - p_novo)*0.3;

    if ( fabs(P - p_novo) < EPS) break;

    // Verificar o número de iterações:
    if (w > MAXITER)
      {
	ERROR_FLAG = 3;
	return;
      }
    // Com os novos valores, calcular o novo valor de rhom:
    Z = 1 + B*rhom + C*rhom*rhom;
    rhom = P/(Z*R*T);
    
      
    //rhom = 1 / ( R*T/P * (1 + B*rhom + C*rhom*rhom));
    
  } while (1);

  // Calcular a compressibilidade:
  Z = 1 + B * rhom + C * rhom * rhom;
  // Calcular a massa específica

}
  
    
      
  
  

