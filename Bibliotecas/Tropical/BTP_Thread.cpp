/*
 ##################################################################
 #                       Objeto Thread                            #
 #               Copyright�:                                      #
 #                Tropical� Corp.                                 #
 #----------------------------------------------------------------#
 #               Modificada em:                                   #
 #               28/06/2006 - Alexandre A. S. Lopes               #
 #              Implementa��o de tratamento de Exce��es           #
 #----------------------------------------------------------------#
 #               29/06/2006 - Alexandre A. S. Lopes               #
 #----------------------------------------------------------------#
 #               16/07/2006 - Alexandre A. S. lopes               #
 #              Mudan�a no sistema de exce��es                    #
 #----------------------------------------------------------------#
 #               28/07/2006 - Alexandre A. S. Lopes               #
 #----------------------------------------------------------------#
 #               09/11/2006 - Alexandre A. S. Lopes               #
 #           Inser��o do sistema de envio de mensagens para janela#
 #----------------------------------------------------------------#
 #               22/02/2007 - Alexandre A. S. Lopes               #
 #----------------------------------------------------------------#
 #               04/04/2007 - Alexandre A. S. Lopes               #
 #----------------------------------------------------------------#
 #               23/06/2008 - Alexandre A. S. Lopes               #
 ##################################################################
*/
//---------------------------------------------------------------------------
#include "BTP_Thread.h"

typedef unsigned (WINAPI *CAST_FUNCTION)(LPVOID);
typedef unsigned *CAST_LPDWORD;

//---------------------------------------------------------------------------
__TROPICALL BTP_Thread::BTP_Thread(char* nome,bool ativa,HWND janela)throw(BTP_Excecao*):BTP_Objeto(nome)
{
  DWORD dwFlagDeCriacao;
  suspensa=ativa;
  Janela=janela;
  
  hthread = NULL;

  if (!suspensa)dwFlagDeCriacao=CREATE_SUSPENDED;
  else dwFlagDeCriacao=NULL;

  hthread = (HANDLE)  _beginthreadex(NULL,
						 NULL,
						 (CAST_FUNCTION)ThreadMain,
						 (LPVOID)this,
						 dwFlagDeCriacao,
						 (CAST_LPDWORD) &dwthreadid);
  if(!hthread)
  {
	throw new BTP_Excecao(this,
						  "Erro ao tentar criar a Thread");

  }



}
//---------------------------------------------------------------------------
__TROPICALL BTP_Thread::~BTP_Thread()
{
   //DWORD Exit;
//   ExitThread(Exit);
   TerminateThread(hthread,0);
   CloseHandle(hthread);
}
//---------------------------------------------------------------------------
void __TROPICALL BTP_Thread::TerminarThread()
{
   TerminateThread(hthread,0);
   CloseHandle(hthread);
   hthread=NULL;

}
//---------------------------------------------------------------------------
void __TROPICALL BTP_Thread::ReiniciarThread()throw(BTP_Excecao*)
{
  if(!hthread)
  {
   DWORD dwFlagDeCriacao=NULL;
   hthread = (HANDLE) _beginthreadex(NULL,
						 NULL,
						 (CAST_FUNCTION)ThreadMain,
						 (LPVOID)this,
						 dwFlagDeCriacao,
						 (CAST_LPDWORD)&dwthreadid);
   if(!hthread)
   {
	 throw new BTP_Excecao(this,
						  "Erro ao tentar criar a Thread");

   }
  }
  else
   throw new BTP_Excecao(this,"N�o foi possivel reiniciar Thread!");

}
//---------------------------------------------------------------------------
void  __TROPICALL BTP_Thread::Objeto()
{

}
//---------------------------------------------------------------------------
void  __TROPICALL BTP_Thread::MandarMsg(unsigned int Msg,WPARAM wparam,
						   LPARAM lparam,HWND temp) throw(BTP_Excecao*)
{
  if(temp)
  {
   PostMessageA(temp,Msg,wparam,lparam);
   return;
  }
  if(!Janela)
   throw new BTP_Excecao(this,"N�o existe janela de destino");

  PostMessageA(Janela,Msg,wparam,lparam);

}
//---------------------------------------------------------------------------
void  __TROPICALL BTP_Thread::EntregarMsg(unsigned int Msg,WPARAM wparam,
					 LPARAM lparam,HWND temp)throw(BTP_Excecao*)
{
  if(temp)
  {
   SendMessageA(temp,Msg,wparam,lparam);
   return;
  }

  if(!Janela)
   throw new BTP_Excecao(this,"N�o existe janela de destino");

  SendMessageA(Janela,Msg,wparam,lparam);

}
//--Fun��es das propriedades-------------------------------------------------
HANDLE __TROPICALL BTP_Thread::PegarHandle()
{
 return hthread;
}
//---------------------------------------------------------------------------
bool  __TROPICALL BTP_Thread::PegarSuspensa()
{
 return suspensa;
}
//---------------------------------------------------------------------------
void  __TROPICALL BTP_Thread::AlterarSuspensa(bool temp)
{
 if (temp)
 {
  suspensa=true;
  ResumeThread(hthread);
 }
 else
 {
  suspensa=false;
  SuspendThread(hthread);
 }
}
//---------------------------------------------------------------------------
DWORD __TROPICALL BTP_Thread::PegarID()
{
 return dwthreadid;
}
//---------------------------------------------------------------------------
int   __TROPICALL BTP_Thread::PegarPrioridadeDaThread()
{
 return GetThreadPriority(hthread);
}
//---------------------------------------------------------------------------
void  __TROPICALL BTP_Thread::AlterarPrioridadeDaThread(int temp) throw(BTP_Excecao*)
{
 if(!(SetProcessPriorityBoost(GetCurrentProcess(),false)) &
   (SetThreadPriorityBoost(hthread,false)) &
   (SetThreadPriority(hthread,temp)))
   {
	 throw new BTP_Excecao(this,
						   "Erro ao tentar mudar a prioridade da Thread");

   }

}
//---------------------------------------------------------------------------
int   __TROPICALL BTP_Thread::PegarPrioridadeDoProcesso()
{
  return GetPriorityClass(GetCurrentProcess());
}
//---------------------------------------------------------------------------
void  __TROPICALL BTP_Thread::AlterarPrioridadeDoProcesso(int temp) throw(BTP_Excecao*)
{
   if(!(SetProcessPriorityBoost(GetCurrentProcess(),false)) &
	 (SetThreadPriorityBoost(hthread,false)) &
	 (SetPriorityClass(GetCurrentProcess(),temp)))
	 {
		  throw new BTP_Excecao(this,
								"Erro ao tentar mudar a prioridade do Processo");
	 }

}
//---------------------------------------------------------------------------
HWND   __TROPICALL BTP_Thread::PegarJanelaMSG()
{
 return Janela;
}
//---------------------------------------------------------------------------
void  __TROPICALL BTP_Thread::AlterarJanelaMSG(HWND temp)
{
 Janela=temp;
}
//---------------------------------------------------------------------------
DWORD WINAPI ThreadMain(LPVOID temp)
{
 BTP_Thread *ThreadClass=(BTP_Thread *)temp;
 ThreadClass->Executar();
 _endthreadex((DWORD) 0);
 return 0;
}
//---------------------------------------------------------------------------


