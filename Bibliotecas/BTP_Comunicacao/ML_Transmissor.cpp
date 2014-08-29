/*##################################################################
  #             Objeto Transmissor de Sequência de impressão       #
  #               Copyright©:                                      #
  #                Tropical® Corp.                                 #
  #----------------------------------------------------------------#
  #               Modificada em:                                   #
  #               26/10/2007  - Alexandre A. S. Lopes              #
  #----------------------------------------------------------------#
  #               14/11/2007  - Alexandre A. S. Lopes              #
  ##################################################################*/
//---------------------------------------------------------------------------


#include "ML_Transmissor.h"
#include <stdio.h>

#include "ML_Opcodes.h"
#include "ML_Definicoes.h"


//---------------------------------------------------------------------------
__TROPICALL ML_Transmissor::ML_Transmissor(char*nome,unsigned int ttamanhodopacote)
																   :BTP_Thread(nome)
{
 tamanhopacote=ttamanhodopacote;
 Transmite=new BTP_Evento("Evento de Transmisão");
 //--Porta Serial--------------
 Porta=new BTP_PortaSerial("Porta Serial de Saida");
 BTP_PortaSerial::BTP_PortaConfig Config=Porta->Config;
 Config.BaudRate = CBR_38400;
 Config.ByteSize = 8;
 Config.Parity = NOPARITY;
 Config.StopBits = ONESTOPBIT;
 Porta->Config=Config;
 //----------------------------
 Porta->EVDadoRecebido=new BTP_Evento("Evento de Dado Recebido");
 BTP_Thread::Ativa=true;
 transmitindo=false;
}
//---------------------------------------------------------------------------
__TROPICALL ML_Transmissor::~ML_Transmissor()
{
 if(Porta->EVDadoRecebido)
   delete Porta->EVDadoRecebido;

 delete Porta;
 delete Transmite;
}
//---------------------------------------------------------------------------
void __TROPICALL ML_Transmissor::Objeto()
{

}
//---------------------------------------------------------------------------
void __TROPICALL ML_Transmissor::Executar()
{
 for(;;)
 {
  try
  {
	PosEnt=0;
	cancelar=false;


	WaitForSingleObject(Transmite->hEvento,INFINITE);
	this->ReiniciarMiniLab();

	BTP_Thread::EntregarMsg(CM_PROGRESSO);



	Porta->TransmitirDados(COM_RECEBER_BUFFER,strlen(COM_RECEBER_BUFFER));


	 this->EsperaResposta();
	 this->TransmiteBuffer();

	 transmitindo=false;
//	 delete [] Buffer.Buffer;

	 if(!cancelar)
	  this->EsperaFim();


	 BTP_Thread::EntregarMsg(CM_FIM);
   }
  catch(BTP_Excecao* Erro)
  {
   transmitindo=false;
   excecao=Erro;
   BTP_Thread::EntregarMsg(CM_BTP_EXCECAO);
  }
  catch(...)
  {
	transmitindo=false;
	BTP_Thread::EntregarMsg(CM_TM_EXCECAO);
  }
 }
}
//---------------------------------------------------------------------------
void __TROPICALL ML_Transmissor::EsperaResposta()
{
 this->EsperaComando();
 //------------------------------------
 if(!this->ProcuraResposta(MC_INICIAR_TRANSFERENCIA))
  throw new BTP_Excecao(this,"Não foi possivel comunicar com o Mini-Lab");
//-------------------------------------
}
//---------------------------------------------------------------------------
void __TROPICALL ML_Transmissor::EsperaFim()
{
 this->EsperaComando();
 //------------------------------------
 if(!this->ProcuraResposta(MC_FIM))
  throw new BTP_Excecao(this,"Não foi possivel comunicar com o Mini-Lab");
//-------------------------------------

}
//---------------------------------------------------------------------------
void __TROPICALL ML_Transmissor::TransmiteBuffer()
{
   transmitindo=true;
	//--Transmitindo Buffer--
   for(unsigned int x=0;x<NumPacotes-1;x++)
   {
	 Porta->TransmitirDados(&Buffer.Buffer[bytestransmitidos],tamanhopacote);
	 bytestransmitidos+=tamanhopacote;
	 if(cancelar)
	 {
	  BTP_Thread::EntregarMsg(CM_CANCELADO);
	  return;
	 }
	 BTP_Thread::EntregarMsg(CM_PROGRESSO);
	 this->EsperaReiniciar();
   }
	Porta->TransmitirDados(&Buffer.Buffer[bytestransmitidos],tamanhopacote);
	bytestransmitidos+=tamanhopacote;
	BTP_Thread::EntregarMsg(CM_PROGRESSO);
}
//---------------------------------------------------------------------------
void __TROPICALL ML_Transmissor::EsperaReiniciar()
{

 this->EsperaComando();
 //------------------------------------
 if(!this->ProcuraResposta(MC_REINICIAR_TRANSFERENCIA))
  throw new BTP_Excecao(this,"Não foi possivel comunicar com o Mini-Lab");
//-------------------------------------
}
//---------------------------------------------------------------------------
bool __TROPICALL ML_Transmissor::ProcuraResposta(char *Cmd)
{
char Temp[200];
char Buffer[200];
unsigned int TamanhoBuffer=0;

 for(unsigned int x=0;x<Porta->TamanhoBuffer;x++)
	Buffer[x]=Porta->Buffer[x];
 TamanhoBuffer=Porta->TamanhoBuffer;

 if((Porta->TamanhoBuffer==(unsigned int)0)||(Porta->TamanhoBuffer<(unsigned int)strlen(Cmd)))
 {
  Sleep(300);
  Porta->ZerarBuffer();
  Porta->ReceberDados();

  for(unsigned int x=0;x<Porta->TamanhoBuffer;x++)
	Buffer[x+TamanhoBuffer]=Porta->Buffer[x];

  TamanhoBuffer+=Porta->TamanhoBuffer;
 }
 for(unsigned int x=0;x<=TamanhoBuffer-strlen(Cmd);x++)
 {
  if(Buffer[x]==Cmd[0])
  {
	for(unsigned int y=0;y<strlen(Cmd);y++)
	 Temp[y]=Buffer[y+x];


   Temp[strlen(Cmd)]='\0';
   if(!strcmp(Temp,Cmd))
	return true;
  }
 }
 return false;
}
//---------------------------------------------------------------------------
void __TROPICALL ML_Transmissor::Transmitir(ML_Buffer buffer)
{
 Buffer=buffer;
 if(Buffer.Tamanho%tamanhopacote)
  throw new BTP_Excecao(this,"Tamanho do buffer não é multiplo do tamanho do pacote!");

 bytestransmitidos=0;
 this->CalcularNumPacotes();

 FILE *Arq=fopen("Config\\Saida.opc","wb");
  fwrite(buffer.Buffer,1,buffer.Tamanho,Arq);
 fclose (Arq);

 Arq=fopen("Config\\BufferConfig.txt","w");
  fprintf(Arq,"O tamanho do Buffer é: %d\n",buffer.Tamanho);
  fprintf(Arq,"O número de pacotes é: %d\n",NumPacotes);
 fclose (Arq);


  Transmite->PulsarEvento();

}
//---------------------------------------------------------------------------
void __TROPICALL ML_Transmissor::CancelarTransmissao()
{
 if(!transmitindo)
  throw new BTP_Excecao(this,"O programa não está transmitindo!");

 Buffer.Buffer[bytestransmitidos+0]=OPC_REINICIAR;
 Buffer.Buffer[bytestransmitidos+1]=OPC_REINICIAR1;
 Buffer.Buffer[bytestransmitidos+2]=OPC_REINICIAR2;
 Buffer.Buffer[bytestransmitidos+3]=OPC_REINICIAR3;

 Buffer.Buffer[bytestransmitidos+30]=OPC_REINICIAR;
 Buffer.Buffer[bytestransmitidos+31]=OPC_REINICIAR1;
 Buffer.Buffer[bytestransmitidos+32]=OPC_REINICIAR2;
 Buffer.Buffer[bytestransmitidos+33]=OPC_REINICIAR3;

 Buffer.Buffer[bytestransmitidos+60]=OPC_REINICIAR;
 Buffer.Buffer[bytestransmitidos+61]=OPC_REINICIAR1;
 Buffer.Buffer[bytestransmitidos+62]=OPC_REINICIAR2;
 Buffer.Buffer[bytestransmitidos+63]=OPC_REINICIAR3;
 cancelar=true;

}
//---------------------------------------------------------------------------
void __TROPICALL ML_Transmissor::ReiniciarMiniLab()
{
  unsigned char *TempBuffer=new unsigned char[tamanhopacote];

   for(unsigned int x=0;x<tamanhopacote;x++)
   {
	if(x%4==0)
	 TempBuffer[x]=OPC_REINICIAR;
	if(x%4==1)
	 TempBuffer[x]=OPC_REINICIAR1;
	if(x%4==2)
	 TempBuffer[x]=OPC_REINICIAR2;
	if(x%4==3)
	 TempBuffer[x]=OPC_REINICIAR3;
   }


  Porta->TransmitirDados(TempBuffer,tamanhopacote);
  Porta->TransmitirDados(COM_REINICIAR_MIC,strlen(COM_REINICIAR_MIC));
  Sleep(100);
  Porta->TransmitirDados(COM_REINICIAR_MIC,strlen(COM_REINICIAR_MIC));


  delete [] TempBuffer;
}
//---------------------------------------------------------------------------
void __TROPICALL ML_Transmissor::CalcularNumPacotes()
{
 float TempNum=(float)(((float)Buffer.Tamanho)/((float)tamanhopacote));
 NumPacotes=TempNum;
 float tempnumpacotes=NumPacotes;
 if(tempnumpacotes<TempNum)
  NumPacotes++;
}
//---------------------------------------------------------------------------
void __TROPICALL ML_Transmissor::EsperaComando()
{
 Porta->HabilitaEventos=true;
for(unsigned x=0;x<1000000;x++)
{
 WaitForSingleObject(Porta->EVDadoRecebido,100);
 Porta->ZerarBuffer();
 Porta->ReceberDados();

 if(Porta->TamanhoBuffer>=3)
  for(unsigned int x=0;x<=Porta->TamanhoBuffer-3;x++)
   if((Porta->Buffer[x]=='C') && (Porta->Buffer[x+1]=='M') && (Porta->Buffer[x+2]=='D'))
   {
	Porta->HabilitaEventos=false;
	return;
   }
}
  Porta->HabilitaEventos=false;
  throw new BTP_Excecao(this,"Não foi possivel comunicar com o Mini-Lab");

}
//--Propriedades-------------------------------------------------------------
unsigned int __TROPICALL ML_Transmissor::PegarBytesTransmitidos()
{
return bytestransmitidos;
}
//---------------------------------------------------------------------------
unsigned int __TROPICALL ML_Transmissor::PegarTamanhoDoPacote()
{
return tamanhopacote;
}
//---------------------------------------------------------------------------
void __TROPICALL ML_Transmissor::AlterarTamanhoDoPacote(unsigned int temp)
{
 tamanhopacote=temp;
}
//---------------------------------------------------------------------------
unsigned int __TROPICALL ML_Transmissor::PegarBytesRestantes()
{
 return Buffer.Tamanho-bytestransmitidos;
}
//---------------------------------------------------------------------------
void __TROPICALL ML_Transmissor::AlterarJanelaMSG(HWND janela)
{
 BTP_Thread::JanelaMSG=janela;
}
//---------------------------------------------------------------------------
bool __TROPICALL ML_Transmissor::PegarPausarTransmissao()
{
 return BTP_Thread::Ativa;
}
//---------------------------------------------------------------------------
void __TROPICALL ML_Transmissor::AlterarPausarTransmissao(bool temp)
{
 BTP_Thread::Ativa=temp;
}
//---------------------------------------------------------------------------
bool __TROPICALL ML_Transmissor::PegarTransmitindo()
{
 return transmitindo;
}
//---------------------------------------------------------------------------
BTP_Excecao* __TROPICALL ML_Transmissor::PegarExcecao()
{
 BTP_Excecao *temp=excecao;
 excecao=NULL;
 return temp;
}
//---------------------------------------------------------------------------
