/*##################################################################
  #             Objeto Transmissor de Sequência de impressão       #
  #               Copyright©:                                      #
  #                Tropical® Corp.                                 #
  #----------------------------------------------------------------#
  #               Criada em:                                       #
  #               20/07/07 - Alexandre A. S. Lopes                 #
  #               Descrição:                                       #
  #             Controle de transmissão de sequencia de impressão  #
  #     ao Mini-Lab                                                #
  ################################################################## */

//---------------------------------------------------------------------------
#ifndef ML_TransmissorH
#define ML_TransmissorH



#include "BTP_PortaSerial.h"
#include "BTP_Evento.h"
#include "BTP_Excecao.h"
#include "ML_MicDef.h"

//--Comando de comunicação------------
#define MC_LIGADO
#define COM_RECEBER_BUFFER          "CMDa"
#define MC_INICIAR_TRANSFERENCIA    "Receber"
#define MC_REINICIAR_TRANSFERENCIA  "Reiniciar"
#define COM_REINICIAR_MIC           "CMDg"
#define MC_FIM                      "Fim"
//------------------------------------

//#define TAMANHO_BUFFER 300

class BIBML_TRANSMISSAO ML_Transmissor :BTP_Thread
{

 void __TROPICALL Objeto();
 ML_Buffer Buffer;
 BTP_PortaSerial *Porta;
 BTP_Evento *Transmite;
 BTP_Excecao *excecao;
 void __TROPICALL Executar();
 unsigned int BufferPos,PosEnt;
 unsigned int bytestransmitidos,tamanhopacote,NumPacotes;
 bool transmitindo,cancelar;

 void __TROPICALL EsperaResposta();
 void __TROPICALL EsperaFim();
 void __TROPICALL TransmiteBuffer();
 void __TROPICALL EsperaReiniciar();
 bool __TROPICALL ProcuraResposta(char *);
 void __TROPICALL CalcularNumPacotes();
 void __TROPICALL EsperaComando();
public:

 __TROPICALL ML_Transmissor(char*,unsigned int ttamanhodopacote);
 __TROPICALL ~ML_Transmissor();

 void __TROPICALL Transmitir(ML_Buffer);
 void __TROPICALL CancelarTransmissao();
 void __TROPICALL ReiniciarMiniLab();



 __property unsigned int BytesTransmitidos = {read=PegarBytesTransmitidos};
 __property unsigned int TamanhoDoPacote = {read=PegarTamanhoDoPacote,
												  write=AlterarTamanhoDoPacote};
 __property unsigned int BytesRestantes = {read=PegarBytesRestantes};
 __property HWND JanelaMSG={write=AlterarJanelaMSG};
 __property bool PausarTransmissao = {read=PegarPausarTransmissao,
											   write=AlterarPausarTransmissao};
 __property bool Transmitindo = {read=PegarTransmitindo};
 __property BTP_Excecao* Excecao = {read=PegarExcecao};

 //--Propriedades------------
 private:
 unsigned int __TROPICALL PegarBytesTransmitidos();
 unsigned int __TROPICALL PegarTamanhoDoPacote();
 void __TROPICALL AlterarTamanhoDoPacote(unsigned int );
 unsigned int __TROPICALL PegarBytesRestantes();
 void __TROPICALL AlterarJanelaMSG(HWND);
 bool __TROPICALL PegarPausarTransmissao();
 void __TROPICALL AlterarPausarTransmissao(bool);
 bool __TROPICALL PegarTransmitindo();
 BTP_Excecao* __TROPICALL PegarExcecao();
};



//---------------------------------------------------------------------------
#endif
