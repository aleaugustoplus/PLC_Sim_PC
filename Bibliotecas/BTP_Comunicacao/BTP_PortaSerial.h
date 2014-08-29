/*##################################################################
  #                Objeto de Comunicação Serial                    #
  #               Copyright©:                                      #
  #                Tropical® Corp.                                 #
  #----------------------------------------------------------------#
  #               Criada em:                                       #
  #               27/05/07 - Alexandre A. S. Lopes                 #
  #               Descrição:                                       #
  #               Classe de controle de comunicação                #
  ##################################################################*/
//---------------------------------------------------------------------------

#ifndef BTP_PortaSerialH
#define BTP_PortaSerialH

#include "BTP_PortaCom.h"
#include "BTP_Excecao.h"
#include "BTP_BufferPorta.h"




#include <windows.h>








class  BTP_PortaSerial :public BTP_PortaCom
{
 public:



 enum BTP_Porta {
				COM1,
				COM2,
				COM3,
				COM4,

 };


 typedef DCB BTP_PortaConfig;
 //obs: Falta Traduzir algumas macros e checar se as traduzidas estão todas corretas
 enum MascaraCom {
				 DETECTADO_PARADA=EV_BREAK,
				 MUNDANCA_DE_SINAL_DE_ENVIO=EV_CTS,
				 MUNDANCA_DE_SINAL_DE_LEITURA=EV_DSR,
				 DETECTADO_CARACTERE=EV_RXCHAR,

 };





 private:

 HANDLE hporta;
 BTP_BufferPorta *bufferport;



 bool __TROPICALL ConfiguraControle();
 bool __TROPICALL ConfiguraTimeOuts();
 void __TROPICALL Objeto();

 public:


 unsigned int tamanhobuffer;
  __TROPICALL BTP_PortaSerial(char *,BTP_Porta=COM1);
 __TROPICALL ~BTP_PortaSerial();


 void __TROPICALL TransmitirDados(Dado *Buffer,unsigned int Tamanho);
 void __TROPICALL LeituraAsinc();
 void __TROPICALL AddEntToBuffer();
 void __TROPICALL TransmitirByte(Dado Buffer);
 Dado __TROPICALL ReceberByte();


 __property HANDLE hPorta = {read = PegarhPorta};
 __property BTP_PortaConfig Config = {read=PegarPortaConfig,write=AlterarPortaConfig};
 __property MascaraCom Mascara = {read=PegarMascara,write=AlterarMascara};
 __property BTP_BufferPorta *BufferPort = {read = PegarBufferPort};
 //--Propriedades------------------
 private:

 HANDLE __TROPICALL PegarhPorta();
 BTP_PortaConfig __TROPICALL PegarPortaConfig();
 void __TROPICALL AlterarPortaConfig(BTP_PortaConfig);
 HANDLE __TROPICALL PegarPorta();
 MascaraCom __TROPICALL PegarMascara();
 void __TROPICALL AlterarMascara(MascaraCom);
 HANDLE __TROPICALL PegarCaractere();
 BTP_BufferPorta *__TROPICALL PegarBufferPort();
};
//---------------------------------------------------------------------------
#endif
