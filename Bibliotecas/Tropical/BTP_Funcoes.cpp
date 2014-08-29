/*##################################################################
  #                    Namespace Tropical                          #
  #----------------------------------------------------------------#
  #               Copyright©:                                      #
  #                Tropical® Corp.                                 #
  #		                                                           #
  #		Desenvolvedor: Alexandre O. Santos                         #
  #		Data: 23/07/2006                                           #
  #                                                                #
  ##################################################################
*/
    
//---------------------------------------------------------------------------
#include "BTP_Funcoes.h"

//---------------------------------------------------------------------------
// Função que retorna um valor sempre positivo de um inteiro ----------------
BIBTROPICAL unsigned int __TROPICALL IntToUint(int Valor)
{
 unsigned int uintValor;

		if(Valor < 0)
		  uintValor = Valor * -1;
		else uintValor = Valor;

 return uintValor;
}
//---------------------------------------------------------------------------


