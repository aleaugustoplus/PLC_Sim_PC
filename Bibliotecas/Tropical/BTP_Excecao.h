/*##################################################################
  #                       Objeto Excecao                           #
  #               Copyright©:                                      #
  #                Tropical® Corp.                                 #
  #----------------------------------------------------------------#
  #               Criada em:                                       #
  #               27/06/06 - Alexandre A. S. lopes                 #
  #               Descrição:                                       #
  #                Classe de tratamento de exceções                #
  ##################################################################*/
//---------------------------------------------------------------------------
#ifndef BTP_ExcecaoH
#define BTP_ExcecaoH
#include "BTP_Objeto.h"

 #ifdef BTP_CONSOLEAPP
  #include <iostream>
 #endif

 #if defined(BTP_MSWIN32)& defined(BTP_WINDOWAPP)
  #include <windows.h>
 #endif


class BIBTROPICAL BTP_Excecao: public BTP_Objeto
{
   void  __TROPICALL Objeto();


 #if defined(BTP_MSWIN32)& defined(BTP_WINDOWAPP)
  public:
  typedef LPTOP_LEVEL_EXCEPTION_FILTER EXCECAO_NAO_CAPTURADA;
  typedef struct _EXCEPTION_POINTERS* PONTEIROS_DE_EXCECOES;
  private:
  static EXCECAO_NAO_CAPTURADA hExcecao_Nao_Capturada;
 #endif

 #ifdef BTP_CONSOLEAPP
  public:
  typedef std::terminate_handler EXCECAO_NAO_CAPTURADA;
  private:
  static std::unexpected_handler Handler_Excecao_Inesperada;
  static EXCECAO_NAO_CAPTURADA hExcecao_Nao_Capturada;
 #endif

 protected:
  BTP_Objeto *Obj;
  char* msgtxt;

 public:

 __TROPICALL BTP_Excecao(BTP_Objeto*,char *tmsgtxt);
 __TROPICALL BTP_Excecao(char *tmsgtxt);
 __TROPICALL ~BTP_Excecao();

 #ifdef BTP_CBUILDER
  __property char* MsgTxt={read=PegarMsgTxt};
 #endif

 #if defined(BTP_MSWIN32)& defined(BTP_WINDOWAPP)
  static void __TROPICALL AlterarHandleExcecao_Nao_Capturada(EXCECAO_NAO_CAPTURADA);
 #endif

 #ifdef BTP_CONSOLEAPP
  static std::unexpected_handler __TROPICALL AlterarHandler_Excecao_Inesperada(std::unexpected_handler);
  static EXCECAO_NAO_CAPTURADA   __TROPICALL AlterarHandler_Excecao_Nao_Capturada(EXCECAO_NAO_CAPTURADA);
 #endif

 //--Propriedades
 #ifdef BTP_CBUIDER
  private:
 #endif

 char* __TROPICALL PegarMsgTxt();

};

//---------------------------------------------------------------------------
#endif
