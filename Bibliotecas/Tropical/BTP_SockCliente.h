/*##################################################################
  #                   Objeto Socket Cliente                        #
  #               Copyright©:                                      #
  #                Tropical® Corp.                                 #
  #----------------------------------------------------------------#
  #               Criada em:                                       #
  #               27/06/06 - Alexandre A. S. lopes                 #
  #               Descrição:      								 #
  #             Classe para conexão de Socket da Tropical® Corp.   #

  ##################################################################
*/

//---------------------------------------------------------------------------

#ifndef BTP_SockClienteH
#define BTP_SockClienteH

#include <windows.h>
#include <winsock2.h>
#include "BTP_Objeto.h"
#include "BTP_Excecao.h"


class BIBTROPICAL BTP_SockCliente : BTP_Objeto
{

 void __TROPICALL Objeto();
 bool conectado;
 SOCKET m_socket;
 WSADATA wsaData;
 sockaddr_in service;
 public:
 typedef unsigned char Byte;

 __TROPICALL BTP_SockCliente(char*)throw(BTP_Excecao*);
 __TROPICALL ~BTP_SockCliente();
 void  __TROPICALL Enviar(char Teste[200]);
 bool  __TROPICALL Aguardar();
 char  __TROPICALL Receber();




};

//---------------------------------------------------------------------------
#endif

