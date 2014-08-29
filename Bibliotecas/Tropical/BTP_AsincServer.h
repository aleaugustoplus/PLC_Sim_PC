/*##################################################################
  #                 Objeto Socket Servidor Assíncrono              #
  #               Copyright©:                                      #
  #                Tropical® Corp.                                 #
  #----------------------------------------------------------------#
  #               Criada em:                                       #
  #               08/11/06 - Alexandre A. S. lopes                 #
  #               Descrição:      								 #
  #             Classe para conexão de Socket da Tropical® Corp.   #
  ##################################################################
*/


#ifndef BTP_AsincServerH
#define BTP_AsincServerH

 #include "BTP_SockServer.h"
 #include "BTP_Thread.h"


class BIBTROPICAL BTP_AsincServer :BTP_Thread, public BTP_SockServer
{
 public:
 enum MsgSockCtrl{CLI_CONECTADO=10001,
				  RECEBIDO=10002
 };

 private:
 char buffer;
 void __TROPICALL Executar();
 public:
 __TROPICALL BTP_AsincServer(char*,HWND janela)throw(BTP_Excecao*);
 __TROPICALL ~BTP_AsincServer();


 #ifdef BTP_CBUILDER
  __property bool  Pausar ={read=PegarPausar, write=AlterarPausar};
  __property char  Buffer ={read=PegarBuffer};
  private:
 #endif                                                          ]
 bool __TROPICALL PegarPausar();
 void __TROPICALL AlterarPausar(bool);
 char __TROPICALL PegarBuffer(); 
};






//---------------------------------------------------------------------------
#endif
