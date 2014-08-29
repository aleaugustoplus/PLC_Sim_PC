/*##################################################################
  #                 Objeto Socket Cliente  Assíncrono              #
  #               Copyright©:                                      #
  #                Tropical® Corp.                                 #
  #----------------------------------------------------------------#
  #               Criada em:                                       #
  #               08/11/06 - Alexandre A. S. lopes                 #
  #               Descrição:      								 #
  #             Classe para conexão de Socket da Tropical® Corp.   #
  ##################################################################*/
//---------------------------------------------------------------------------

#ifndef BTP_AsincClienteH
#define BTP_AsincClienteH

 #include "BTP_SockCliente.h"
 #include "BTP_Thread.h"


class BIBTROPICAL BTP_AsincCliente :BTP_Thread, public BTP_SockCliente
{
 public:
 enum MsgSockCtrl{SERVER_CONECTADO=10001,
				  RECEBIDO=10002
 };

 private:
 char buffer;
 void __TROPICALL Executar();
 public:
 __TROPICALL BTP_AsincCliente(char*,HWND janela)throw(BTP_Excecao*);
 __TROPICALL ~BTP_AsincCliente();


 #ifdef BTP_CBUILDER
  __property bool  Pausar ={read=PegarPausar, write=AlterarPausar};
  __property char* Buffer ={read=PegarBuffer};
  private:
 #endif
 bool  __TROPICALL PegarPausar();
 void  __TROPICALL AlterarPausar(bool);
 char  __TROPICALL PegarBuffer();
};






//---------------------------------------------------------------------------
#endif
