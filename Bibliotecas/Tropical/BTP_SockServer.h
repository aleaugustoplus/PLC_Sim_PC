/*##################################################################
  #                    Objeto Socket Servidor                      #
  #               Copyright©:                                      #
  #                Tropical® Corp.                                 #
  #----------------------------------------------------------------#
  #               Criada em:                                       #
  #               08/11/06 - Alexandre A. S. lopes                 #
  #               Descrição:      								 #
  #             Classe para conexão de Socket da Tropical® Corp.   #
  ##################################################################
*///---------------------------------------------------------------------------

#ifndef BTP_SockServerH
#define BTP_SockServerH



 #include <windows.h>
 #include <winsock2.h>
 #include "BTP_Objeto.h"
 #include "BTP_Excecao.h"


class BIBTROPICAL BTP_SockServer : BTP_Objeto
{
 public:

 typedef unsigned char Byte;
 typedef char* EnderecoIP;

 protected:

 unsigned short Porta;
 EnderecoIP EndIP;
 bool conectado;
 char PCNome[100];

 SOCKET Tomada;
 WSADATA wsaData;
 sockaddr_in servico;

  void __TROPICALL Objeto();
 public:



 __TROPICALL BTP_SockServer(char*,unsigned short porta=27015) throw(BTP_Excecao*);
 __TROPICALL ~BTP_SockServer();
 void  __TROPICALL Enviar(char);
 void  __TROPICALL AguardarConexao() throw(BTP_Excecao*);
 char  __TROPICALL Receber()         throw(BTP_Excecao*);

 #ifdef BTP_CBUILDER
 __property SOCKET Socket = {read=PegarSocket};

  private:
 #endif
 //--Propriedades--

 SOCKET __TROPICALL PegarSocket();




};

//---------------------------------------------------------------------------
#endif
