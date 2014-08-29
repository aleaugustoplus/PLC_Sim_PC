/*##################################################################
  #           Arquivo de defini��es de Pr� Compila��o              #
  #               Copyright�:                                      #
  #                Tropical� Corp.                                 #
  #----------------------------------------------------------------#
  #               Criada em:                                       #
  #               19/11/07 - Alexandre A. S. lopes                 #
  #               Descri��o:                                       #
  #            Arquivo de Pr�-Compila��o do m�dulo ML_Transmissao  #
  #----------------------------------------------------------------#
  #               Modificada em:                                   #
  ##################################################################
*/
//Defini��es de Pr�-Compila��o

//--Defini��o de liga��o--------------------------------------------------------
//#define ML_TRANSMISSAO_LINKDINAMICO
#define ML_TRANSMISSAO_LINKESTATICO
//#define ML_TRANSMISSAO_DLLLINK

#if defined(ML_TRANSMISSAO_LINKDINAMICO) && defined(ML_TRANSMISSAO_LINKESTATICO)
 #error "Dupla definicao de ligacao"
#endif
//--Defini��o de Importa��o---------------------------------------------------
#ifdef ML_TRANSMISSAO_LINKDINAMICO
 #define BIBML_TRANSMISSAO __declspec(dllimport)
#endif

#ifdef ML_TRANSMISSAO_LINKESTATICO
 #define BIBML_TRANSMISSAO
#endif

#ifdef ML_TRANSMISSAO_DLLLINK
 #define BIBML_TRANSMISSAO __declspec(dllexport)
#endif

