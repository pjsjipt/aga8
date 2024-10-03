/** \file \brief aga8_gross.h. Este � o header file da biblioteca aga8_gross. 


A aga8_gross implementa o c�lculo da
compressibilidade natural do g�s natural utilizando a aga8, modo simplificado. O modo
simplificado n�o exige um conhecimento detalhado da composi��o do g�s, apenas
alguns par�metros fixos s�o utilizados. Na realidade implementado segundo a ISO 12213-3.
 */

/** \brief Classe que calcula a compressibilidade natural do g�s natural utilizando
    o m�todo simplificado

    Esta classe implementa o c�lculo da compressibilidade do g�s natural segundo a norma
    ISO 12213-3:1997(E). Esta norma nada mais � que a vers�o ISO da AGA8.
*/
class Aga8_gross
{
 private:
  static const double Tn = 273.15; ///< Temperatura de refer�ncia (normal) K
  static const double Pn = 1.01325; ///< Press�o de refer�ncia (normal) bar
  static const double H_H2 = 285.83; ///< Calor de combust�o do hidrog�nio, MJ/kmol 
  static const double H_CO = 282.98; ///< Calor de combust�o do CO, MJ/kmol

  static const double M_N2 = 28.0135; ///< Massa at�mica do N2, kg/kmol
  static const double M_CO2 = 44.010; ///< Massa at�mica do CO2, kg/kmol
  static const double M_H2 = 2.0159; ///< Massa at�mica do H2, kg/kmol
  static const double M_CO = 28.010; ///< Massa at�mica do CO, kg/kmol
  static const double R = 0.0831451; ///< Constante universal dos gases, m3.bar/(kmol.K)
  static const double V_mn_id = 22.414097; ///< Volume de 1kmol para condi��es normais (0oC, 1atm)
  static const double rho_air = 1.292923; ///< Massa espc�fica do ar seco �s condi��es normais.

  static const double EPS = 1e-6; ///< Crit�rio de converg�ncia
  static const int MAXITER = 100; ///< N�mero m�ximo de itera��es

  static const int CH_ = 0;
  static const int N2_ = 1;
  static const int CO2_ = 2;
  static const int H2_ = 3;
  static const int CO_ = 4;

  
  // Vari�veis internas
  double rho_n;
  double rho_n_calc;///< Massa espec�fica do g�s nas condi��es normais
  double rho_mn;

  double x_CH; 			///< Fra��o molar do hidrocarboneto equivalente
  double x_N2;			///< Fra��o molar de nitrog�nio
  double x_CO2;			///< Fra��o molar de di�xido de carbono
  double x_H2;			///< Fra��o molar de hidrog�nio
  double x_CO;			///< Fra��o molar de mon�xido de carbono

  double H_CH;			///< Calor de combust�o do hidrocarboneto equivalente, MJ/kmol
  double M_CH; 			///< Massa molecular do hidrocarboneto equivalente, kg/kmol

  double Hs;                    ///< Poder calor�fico superior da mistura, MJ/m3
  double d;			///< Densidade relativa do g�s em rela��o ao ar


  double Bn;			///< Primeiro coeficiente virial para condi��es normais


  int ERROR_FLAG;
  /// Fun��o para calcular um polin�mio de segundo grau
  double poly2(double x, double b[]) { return b[0] + b[1]*x + b[2]*x*x; } // Polin�mio de 2 grau

  /// Fun��o que calcula a massa molecular do hidrocarboneto equivalente 
  /** M�todo que calcula a massa molecular do hidrocarboneto equivalente a partir do calor de
      combust�o dos hidrocarbonetos H_CH. em MJ/kmol
      Implementa��o da equa��o B.5 da ISO 12213-3


      \param h_ch Calor de combust�o referido a 25oC em MJ/kmol do hidrocarboneto equivalente
      \return Massa molecular do hidrocarboneto equivalente em kg/kmol
   */
  double calc_M_CH(double h_ch) { return -2.709328 + 0.021062199 * h_ch; } // Calcula a massa molecular
                                                             // de CH para diferente calores de combust�o

  double calc_rho(double H);	///< Calcula a massa espe�ifica em condi��es normais
  
  
  
  
public:
  
  double BVIRIAL(double T);	///< Calcula o segundo coeficiente virial
  double CVIRIAL(double T);	///< Calcula o terceiro coeficiente virial

  double MW;			///< Mass molecular da mistura em kg/kmol

  int error(void) { return ERROR_FLAG; }
  

  /// Fun��o que retorna as concentra��es  dos compostos no g�s natural
  void concentration(double *N2, double *CO2, double *H2, double *CO);

  /// Especifica a composi��o. Dados de entrada: Hs, d, xCO2, xH2, xCO
  void set_A(double HHs, double dd, double xx_CO2, double xx_H2 = 0.0, double xx_CO=0.0);	// Conjunto de dados de entrada A

  /// Espcifica a composi��o. Dados de entrada: d, xN2, xCO2, xH2, xCO
  void set_B(double dd, double xx_N2, double xx_CO2, double xx_H2 = 0.0, double xx_CO = 0.0);

  /// Calcula os diversos a compressiblidade, a densidade molar e a densidade a partir da temperatura e press�o 
  void calc(double P, double T, double &Z, double &rhom, double &rho); // Calculo dos diversos par�metros

  

};




  
  
