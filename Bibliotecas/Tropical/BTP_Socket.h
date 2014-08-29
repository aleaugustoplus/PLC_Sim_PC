/*##################################################################
  #                         Objeto Socket                          #
  #               Copyright©:                                      #
  #                Tropical® Corp.                                 #
  #----------------------------------------------------------------#
  #               Criada em:                                       #
  #               08/11/06 - Alexandre A. S. lopes                 #
  #               Descrição:      								 #
  #             Classe para conexão de Socket da Tropical® Corp.   #
  ##################################################################
*/


//---------------------------------------------------------------------------
#ifndef BTP_SocketH
 #define BTP_SocketH

#include <windows.h>
#include <winsock2.h>
#include "BTP_Objeto.h"
#include "BTP_Excecao.h"





class BIBTROPICAL BTP_Socket : BTP_Objeto
{
 public:
 enum TipoDeSocket{
  CLIENTE,
  SERVIDOR
 };
 typedef unsigned char Byte;
 typedef char* EnderecoIP;

 protected:
 TipoDeSocket Tipo;
 unsigned short Porta;
 EnderecoIP EndIP;
 bool conectado;

 SOCKET tomada;
 WSADATA wsaData;
 sockaddr_in servico;

  void __TROPICALL Objeto();
 public:



 __TROPICALL BTP_Socket(char*,TipoDeSocket,EnderecoIP endip="127.0.0.1",unsigned short porta=27015) throw(BTP_Excecao*);
 __TROPICALL ~BTP_Socket();
 void __TROPICALL Enviar(char);
 void __TROPICALL AguardarConexao()throw(BTP_Excecao*);
 char* __TROPICALL Receber()throw(BTP_Excecao*);

 #ifdef BTP_CBUILDER


 __property SOCKET Socket = {read=PegarSocket};


  private:
 #endif
 //--Propriedades--

 SOCKET __TROPICALL PegarSocket();




};

//---------------------------------------------------------------------------
#endif
