/*##################################################################
  #           Arquivo de definições de Pré Compilação              #
  #               Copyright©:                                      #
  #                Tropical® Corp.                                 #
  #----------------------------------------------------------------#
  #               Criada em:                                       #
  #               19/11/07 - Alexandre A. S. lopes                 #
  #               Descrição:                                       #
  #            Arquivo de Pré-Compilação do módulo ML_Transmissao  #
  #----------------------------------------------------------------#
  #               Modificada em:                                   #
  ##################################################################
*/
//Definições de Pré-Compilação

//--Definição de ligação--------------------------------------------------------
//#define ML_TRANSMISSAO_LINKDINAMICO
#define ML_TRANSMISSAO_LINKESTATICO
//#define ML_TRANSMISSAO_DLLLINK

#if defined(ML_TRANSMISSAO_LINKDINAMICO) && defined(ML_TRANSMISSAO_LINKESTATICO)
 #error "Dupla definicao de ligacao"
#endif
//--Definição de Importação---------------------------------------------------
#ifdef ML_TRANSMISSAO_LINKDINAMICO
 #define BIBML_TRANSMISSAO __declspec(dllimport)
#endif

#ifdef ML_TRANSMISSAO_LINKESTATICO
 #define BIBML_TRANSMISSAO
#endif

#ifdef ML_TRANSMISSAO_DLLLINK
 #define BIBML_TRANSMISSAO __declspec(dllexport)
#endif

