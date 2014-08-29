/*##################################################################
  #                       Objeto Excecao                           #
  #               Copyright©:                                      #
  #                Tropical® Corp.                                 #
  #----------------------------------------------------------------#
  #               Modificada em:                                   #
  #               28/06/2006 - Alexandre A. S. Lopes               #
  #----------------------------------------------------------------#
  #               07/07/2006 - Alexandre A. S. Lopes               #
  #----------------------------------------------------------------#
  #               16/07/2006 - Alexandre A. S. Lopes               #
  #              Mudança no sistema de tratamento de exceções      #
  #              Inserção das funções de excecoes inesperadas e    #
  #       Témino inesperado                                        #
  #----------------------------------------------------------------#
  #               17/07/2006 - Alexandre A. S. Lopes               #
  #----------------------------------------------------------------#
  #               21/07/2006 - Alexandre A. S. Lopes               #
  #----------------------------------------------------------------#
  #               18/01/2007 - Alexandre A. S. Lopes               #
  #               Alteração na forma de armazenamento das mensagens#
  #       de erro.                                                 #
  ##################################################################
*/
#include "BTP_Excecao.h"
#include <string.h>
//---------------------------------------------------------------------------
__TROPICALL BTP_Excecao::BTP_Excecao(BTP_Objeto *temp,char *tmsgtxt):BTP_Objeto(NULL)
{
 Obj=temp;
 #ifdef BTP_CBUILDER
  BTP_Objeto::AlterarMudaNome(Obj->Nome);
 #endif
 #ifndef BTP_CBUILDER
  BTP_Objeto::AlterarMudaNome(Obj->PegarNome());
 #endif
 msgtxt=new char[strlen(tmsgtxt)+1];
 strcpy(msgtxt,tmsgtxt);
}
//---------------------------------------------------------------------------
__TROPICALL BTP_Excecao::BTP_Excecao(char *tmsgtxt):BTP_Objeto(NULL)
{
 msgtxt=new char[strlen(tmsgtxt)+1];
 strcpy(msgtxt,tmsgtxt);
}
//---------------------------------------------------------------------------
__TROPICALL BTP_Excecao::~BTP_Excecao()
{
 delete []msgtxt;
}
//---------------------------------------------------------------------------
void __TROPICALL BTP_Excecao::Objeto()
{
}
//---------------------------------------------------------------------------
#ifdef BTP_CONSOLEAPP
 std::unexpected_handler BTP_Excecao::Handler_Excecao_Inesperada=0;
 BTP_Excecao::EXCECAO_NAO_CAPTURADA __TROPICALL BTP_Excecao::hExcecao_Nao_Capturada=0;
 //---------------------------------------------------------------------------
 std::unexpected_handler __TROPICALL BTP_Excecao::AlterarHandler_Excecao_Inesperada
												(std::unexpected_handler temp)
 {
  Handler_Excecao_Inesperada=temp;
  return std::set_unexpected(Handler_Excecao_Inesperada);

 }
 //---------------------------------------------------------------------------
 std::terminate_handler __TROPICALL BTP_Excecao::AlterarHandler_Excecao_Nao_Capturada
												 (EXCECAO_NAO_CAPTURADA temp)
 {
  hExcecao_Nao_Capturada=temp;
  return std::set_terminate(hExcecao_Nao_Capturada);
 }
#endif
//---------------------------------------------------------------------------
 #if defined(BTP_MSWIN32)& defined(BTP_WINDOWAPP)
  BTP_Excecao::EXCECAO_NAO_CAPTURADA BTP_Excecao::hExcecao_Nao_Capturada=0;
 //--------------------------------------------------------------------------
  void __TROPICALL BTP_Excecao::AlterarHandleExcecao_Nao_Capturada
												(EXCECAO_NAO_CAPTURADA temp)
  {
   hExcecao_Nao_Capturada=temp;
   SetUnhandledExceptionFilter(hExcecao_Nao_Capturada);
  }

 #endif
//--Propriedades-------------------------------------------------------------
char* __TROPICALL BTP_Excecao::PegarMsgTxt()
{
 return msgtxt;
}
//---------------------------------------------------------------------------



