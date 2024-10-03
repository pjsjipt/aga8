/** \file \brief aga8_gross.h. Este ó o header file da biblioteca aga8_gross. 


A aga8_gross implementa o cálculo da
compressibilidade natural do gás natural utilizando a aga8, modo simplificado. O modo
simplificado não exige um conhecimento detalhado da composição do gás, apenas
alguns parâmetros fixos são utilizados. Na realidade implementado segundo a ISO 12213-3.
 */

/** \brief Classe que calcula a compressibilidade natural do gás natural utilizando
    o método simplificado

    Esta classe implementa o cálculo da compressibilidade do gás natural segundo a norma
    ISO 12213-3:1997(E). Esta norma nada mais é que a versão ISO da AGA8.
*/
class Aga8_gross
{
 private:
  static const double Tn = 273.15; ///< Temperatura de referência (normal) K
  static const double Pn = 1.01325; ///< Pressão de referência (normal) bar
  static const double H_H2 = 285.83; ///< Calor de combustão do hidrogênio, MJ/kmol 
  static const double H_CO = 282.98; ///< Calor de combustão do CO, MJ/kmol

  static const double M_N2 = 28.0135; ///< Massa atômica do N2, kg/kmol
  static const double M_CO2 = 44.010; ///< Massa atômica do CO2, kg/kmol
  static const double M_H2 = 2.0159; ///< Massa atômica do H2, kg/kmol
  static const double M_CO = 28.010; ///< Massa atômica do CO, kg/kmol
  static const double R = 0.0831451; ///< Constante universal dos gases, m3.bar/(kmol.K)
  static const double V_mn_id = 22.414097; ///< Volume de 1kmol para condições normais (0oC, 1atm)
  static const double rho_air = 1.292923; ///< Massa espcífica do ar seco às condições normais.

  static const double EPS = 1e-6; ///< Critério de convergência
  static const int MAXITER = 100; ///< Número máximo de iterações

  static const int CH_ = 0;
  static const int N2_ = 1;
  static const int CO2_ = 2;
  static const int H2_ = 3;
  static const int CO_ = 4;

  
  // Variáveis internas
  double rho_n;
  double rho_n_calc;///< Massa específica do gás nas condições normais
  double rho_mn;

  double x_CH; 			///< Fração molar do hidrocarboneto equivalente
  double x_N2;			///< Fração molar de nitrogênio
  double x_CO2;			///< Fração molar de dióxido de carbono
  double x_H2;			///< Fração molar de hidrogênio
  double x_CO;			///< Fração molar de monóxido de carbono

  double H_CH;			///< Calor de combustão do hidrocarboneto equivalente, MJ/kmol
  double M_CH; 			///< Massa molecular do hidrocarboneto equivalente, kg/kmol

  double Hs;                    ///< Poder calorífico superior da mistura, MJ/m3
  double d;			///< Densidade relativa do gás em relação ao ar


  double Bn;			///< Primeiro coeficiente virial para condições normais


  int ERROR_FLAG;
  /// Função para calcular um polinômio de segundo grau
  double poly2(double x, double b[]) { return b[0] + b[1]*x + b[2]*x*x; } // Polinômio de 2 grau

  /// Função que calcula a massa molecular do hidrocarboneto equivalente 
  /** Método que calcula a massa molecular do hidrocarboneto equivalente a partir do calor de
      combustão dos hidrocarbonetos H_CH. em MJ/kmol
      Implementação da equação B.5 da ISO 12213-3


      \param h_ch Calor de combustão referido a 25oC em MJ/kmol do hidrocarboneto equivalente
      \return Massa molecular do hidrocarboneto equivalente em kg/kmol
   */
  double calc_M_CH(double h_ch) { return -2.709328 + 0.021062199 * h_ch; } // Calcula a massa molecular
                                                             // de CH para diferente calores de combustão

  double calc_rho(double H);	///< Calcula a massa espeçifica em condições normais
  
  
  
  
public:
  
  double BVIRIAL(double T);	///< Calcula o segundo coeficiente virial
  double CVIRIAL(double T);	///< Calcula o terceiro coeficiente virial

  double MW;			///< Mass molecular da mistura em kg/kmol

  int error(void) { return ERROR_FLAG; }
  

  /// Função que retorna as concentrações  dos compostos no gás natural
  void concentration(double *N2, double *CO2, double *H2, double *CO);

  /// Especifica a composição. Dados de entrada: Hs, d, xCO2, xH2, xCO
  void set_A(double HHs, double dd, double xx_CO2, double xx_H2 = 0.0, double xx_CO=0.0);	// Conjunto de dados de entrada A

  /// Espcifica a composição. Dados de entrada: d, xN2, xCO2, xH2, xCO
  void set_B(double dd, double xx_N2, double xx_CO2, double xx_H2 = 0.0, double xx_CO = 0.0);

  /// Calcula os diversos a compressiblidade, a densidade molar e a densidade a partir da temperatura e pressão 
  void calc(double P, double T, double &Z, double &rhom, double &rho); // Calculo dos diversos parâmetros

  

};




  
  
