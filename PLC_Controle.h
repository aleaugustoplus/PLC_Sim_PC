/*##################################################################
  #                Objeto Controle de PLC                          #
  #               Copyright©:                                      #
  #                Noname® Corp.                                   #
  #----------------------------------------------------------------#
  #               Criada em:                                       #
  #               24/06/08 - Alexandre A. S. lopes                 #
  #               Descrição:                                       #
  #                Classe de controle de PLC                       #
  ##################################################################*/

//---------------------------------------------------------------------------

#ifndef PLC_ControleH
#define PLC_ControleH


#include "BTP_Thread.h"
#include "BTP_PortaSerial.h"
#include "BTP_CompletionPort.h"


#define NUM_SAIDAS_D   4
#define NUM_ENTRADAS_D 4


class PLC_Controle: public BTP_Thread
{
 public:
	enum PLC_CTRL_MSG{
					   PLC_BTP_EXCECAO = 10000,
					   PLC_EXCECAO =     10001,
					   PLC_NAO_RESPONDE  = 10002,
					   PLC_MUDOU_ENT = 10003,
					   PLC_MUDOU_SAIDA = 10004,


	};



 private:
 typedef struct _StatusPortas {
	 bool Saidas[NUM_SAIDAS_D];
	 bool Entradas[NUM_ENTRADAS_D];

}StatusPortas;

 StatusPortas Portas;

 BTP_Excecao * excecao;
 BTP_PortaSerial *PortaCom;
 BTP_CompletionPort * CompletionPort;
 DWORD threadmsg;
 HWND  janelamsg;

 unsigned short numsaidasdigitais,numentradasdigitais;
 void __TROPICALL Executar();
 void __TROPICALL AtualizarEntradasD(unsigned int BufferPos);
 void __TROPICALL AtualizarSaidasD(unsigned int BufferPos);
 void __TROPICALL EntregarMsg(unsigned int);

 public:

 __TROPICALL PLC_Controle(char*);
 __TROPICALL ~PLC_Controle();

 __property unsigned short NumSaidasDigitais = {read = PegarNumSaidasDigitais};
 __property bool SaidasDigitais [unsigned short Num] = {read = PegarSaidasDigitais , write =
								   AlterarSaidasDigitais};

 __property unsigned short NumEntradasDigitais = {read = PegarNumEntradasDigitais};

 __property bool EntradasDigitais [unsigned short Num] = {read = PegarEntradasDigitais , write =
								   AlterarEntradasDigitais};
 __property BTP_Excecao * Excecao = {read = PegarExcecao};
 __property DWORD ThreadMsg = {read = PegarThreadMsg , write = AlterarThreadMsg };
 __property HWND  JanelaMsg = {read = PegarJanelaMsg , write = AlterarJanelaMsg};

 //--Propriedades--------------------------
 private:

 unsigned short __TROPICALL PegarNumSaidasDigitais();
 bool __TROPICALL PegarSaidasDigitais(unsigned short Num);
 void __TROPICALL AlterarSaidasDigitais(unsigned short Num,bool);

 unsigned short __TROPICALL PegarNumEntradasDigitais();
 bool __TROPICALL PegarEntradasDigitais(unsigned short Num);
 void __TROPICALL AlterarEntradasDigitais(unsigned short Num,bool);
 BTP_Excecao * __TROPICALL PegarExcecao();

 DWORD __TROPICALL PegarThreadMsg();
 void __TROPICALL AlterarThreadMsg(DWORD);
 HWND __TROPICALL PegarJanelaMsg();
 void __TROPICALL AlterarJanelaMsg(HWND);

 };
//---------------------------------------------------------------------------
#endif
