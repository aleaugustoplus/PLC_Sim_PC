/*##################################################################
  #                Objeto Controle de PLC                          #
  #               Copyright�:                                      #
  #                Noname� Corp.                                   #
  #----------------------------------------------------------------#
  #                Modificado em:                                  #
  #                24/06/2008 - Alexandre A. S. Lopes              #
  #----------------------------------------------------------------#
  #                25/06/2008 - Alexandre A. S. Lopes              #
  ##################################################################*/

//---------------------------------------------------------------------------

#include "PLC_Controle.h"
#include <stdio.h>



//---------------------------------------------------------------------------
__TROPICALL PLC_Controle::PLC_Controle(char*Nome):BTP_Thread(Nome,false)
{
 numsaidasdigitais =   NUM_SAIDAS_D;
 numentradasdigitais = NUM_ENTRADAS_D;
 excecao = NULL;

 janelamsg=NULL;
 threadmsg=NULL;



 for(unsigned short x=0;x<numsaidasdigitais;x++)
  Portas.Saidas[x]=false;

 for(unsigned short x=0;x<numentradasdigitais;x++)
  Portas.Entradas[x]=false;

 PortaCom = new BTP_PortaSerial("Porta de comunicacao");
 CompletionPort = new BTP_CompletionPort("Completion Port");
 CompletionPort->AssociarArquivo(PortaCom);



 BTP_Thread::Ativa = true;
 Sleep(500);




 PortaCom->LeituraAsinc();
}
//---------------------------------------------------------------------------
__TROPICALL PLC_Controle::~PLC_Controle()
{
 delete CompletionPort;
 delete PortaCom;
}
//---------------------------------------------------------------------------
void __TROPICALL PLC_Controle::Executar()
{

  BOOL    bResult;
  DWORD   NumRead;
  BTP_BufferPorta *Buffer;
  OVERLAPPED *lpOver;
  

 try
 {
  for(;;)
  {
	bResult = GetQueuedCompletionStatus(
			   CompletionPort->hHandle,
			   &NumRead,
			   &(DWORD)Buffer,
			   &lpOver,
			   INFINITE
			);

										   

		if (bResult == FALSE && lpOver == NULL) {
			//IssueRead(pCntx);
//			FatalError(
//				"ThreadFunc - Illegal call to GetQueuedCompletionStatus");
		}
		else if (bResult == FALSE && lpOver != NULL) {
			//de;
			//fprintf(stderr,"ThreadFunc - I/O operation failed\n");
		}
		else if (NumRead == 0)
		{

			PortaCom->LeituraAsinc();

			continue;
		}
		else
		{
			Buffer->AddInBufferStr();
			if (Buffer->Entrada == 10 )
			{
             //Este aki
			 printf("%s",Buffer->BufferStr);

			 if(Buffer->BufferStr[0]=='E'&&Buffer->BufferStr[1]=='D')
			  AtualizarEntradasD(2);

			 if(Buffer->BufferStr[0]=='S'&&Buffer->BufferStr[1]=='D')
			  AtualizarSaidasD(2);


			 Buffer->LimparBufferStr();
			}

//			printf("%c\n",Buffer->Entrada);
			PortaCom->LeituraAsinc();

		}
	}
  }
  catch(BTP_Excecao*Erro)
  {
	  excecao=Erro;
	  EntregarMsg(PLC_BTP_EXCECAO);
  }
  catch(...)
  {
	  EntregarMsg(PLC_EXCECAO);
  }



}
//---------------------------------------------------------------------------
void __TROPICALL PLC_Controle::AtualizarEntradasD(unsigned int BufferPos)
{
 unsigned short y =0;

 for(unsigned int x = BufferPos;;x++)
 {

  if(PortaCom->BufferPort->BufferStr[x]=='\0')
   break;


  if(PortaCom->BufferPort->BufferStr[x]=='0')
  {
   if(Portas.Entradas[y])
	EntregarMsg(PLC_MUDOU_ENT);

   Portas.Entradas[y] = false;
  }
  else
  {
   if(!Portas.Entradas[y])
	EntregarMsg(PLC_MUDOU_ENT);

   Portas.Entradas[y] = true;
  }



  y++;
  if(y >= numentradasdigitais )
   break;
 }


}
//---------------------------------------------------------------------------
void __TROPICALL PLC_Controle::AtualizarSaidasD(unsigned int BufferPos)
{
 unsigned short y =0;

 for(unsigned int x = BufferPos;;x++)
 {

  if(PortaCom->BufferPort->BufferStr[x]=='\0')
   break;


  if(PortaCom->BufferPort->BufferStr[x]=='0')
  {
   if(Portas.Saidas[y])
	EntregarMsg(PLC_MUDOU_ENT);

   Portas.Saidas[y] = false;
  }
  else
  {
   if(!Portas.Saidas[y])
	EntregarMsg(PLC_MUDOU_ENT);

   Portas.Saidas[y] = true;
  }



  y++;
  if(y >= numsaidasdigitais )
   break;
 }


}
//---------------------------------------------------------------------------
void __TROPICALL PLC_Controle::EntregarMsg(unsigned int Msg)
{
 if(janelamsg)
  SendMessageA(janelamsg,Msg,0,0);
 if(threadmsg)
  PostThreadMessage(threadmsg,Msg,0,0);
}
//--Propriedades-------------------------------------------------------------
unsigned short __TROPICALL PLC_Controle::PegarNumSaidasDigitais()
{
 return numsaidasdigitais;
}
//---------------------------------------------------------------------------
bool __TROPICALL PLC_Controle::PegarSaidasDigitais(unsigned short Num)
{
 return Portas.Saidas[Num];
}
//---------------------------------------------------------------------------
void __TROPICALL PLC_Controle::AlterarSaidasDigitais(unsigned short Num,bool temp)
{
 if(Portas.Saidas[Num]!=temp)
 {
  char Msg[15];
  if(temp)
   sprintf(Msg,"CMDS%dT%c%c",Num,13,10);
  else
   sprintf(Msg,"CMDS%dF%c%c",Num,13,10);
  BTP_Thread::Ativa = false;
   PortaCom->TransmitirDados(Msg,strlen(Msg));
  BTP_Thread::Ativa = true; 
 }

 Portas.Saidas[Num]=temp;
}
//---------------------------------------------------------------------------
unsigned short __TROPICALL PLC_Controle::PegarNumEntradasDigitais()
{
 return numentradasdigitais;
}
//---------------------------------------------------------------------------
bool __TROPICALL PLC_Controle::PegarEntradasDigitais(unsigned short Num)
{
 return Portas.Entradas[Num];
}
//---------------------------------------------------------------------------
void __TROPICALL PLC_Controle::AlterarEntradasDigitais(unsigned short Num,bool temp)
{
  Portas.Entradas[Num] = temp;
}
//---------------------------------------------------------------------------
BTP_Excecao * __TROPICALL PLC_Controle::PegarExcecao()
{
  BTP_Excecao *temp = excecao;
  excecao = NULL;
  return temp;
}
//---------------------------------------------------------------------------
DWORD __TROPICALL PLC_Controle::PegarThreadMsg()
{
  return threadmsg;
}
//---------------------------------------------------------------------------
void __TROPICALL PLC_Controle::AlterarThreadMsg(DWORD temp)
{
 threadmsg=temp;
}
//---------------------------------------------------------------------------
HWND __TROPICALL PLC_Controle::PegarJanelaMsg()
{
 return janelamsg;
}
//--------------------------------------------------------------------------
void __TROPICALL PLC_Controle::AlterarJanelaMsg(HWND temp)
{
 janelamsg = temp;
}
//---------------------------------------------------------------------------
