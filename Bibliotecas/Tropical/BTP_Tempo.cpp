/*##################################################################
  #                    Objeto Temporizador                         #
  #               Copyright©:                                      #
  #                Tropical® Corp.                                 #
  #----------------------------------------------------------------#
  #               Modificada em:                                   #
  #               28/06/2006 - Alexandre A. S. Lopes               #
  #----------------------------------------------------------------#
  #               16/07/2006 - Alexandre A. S. lopes               #
  #              Mudança no sistema de exceções                    #
  #----------------------------------------------------------------#
  #               28/07/2006 - Alexandre A. S. Lopes               #
  #----------------------------------------------------------------#
  #               11/08/2006 - Alexandre A. S. lopes               # 
  ##################################################################
*/
#include "BTP_Tempo.h"

//---------------------------------------------------------------------------
int BTP_Tempo::numtempo=0;
//---------------------------------------------------------------------------
__TROPICALL BTP_Tempo::BTP_Tempo(char *tnome,bool ativarmanual) throw(BTP_Excecao*):BTP_Objeto(tnome)
{
	   BTP_Tempo::numtempo++;

	   char a[50];
	   itoa(BTP_Tempo::numtempo,a,10);
	   strcat(tnome,a);
	   manual=ativarmanual;
	   htimer = CreateWaitableTimerA(NULL, ativarmanual,tnome);
	   ativo=false;
	   intervalo=0;
	   //MessageBoxA(0,tnome,"nome timer",0);
	
}
//---------------------------------------------------------------------------
__TROPICALL BTP_Tempo::~BTP_Tempo()
{
 CloseHandle(htimer);
 BTP_Tempo::numtempo--;
}
//----------------------------------------------------------------------------
void  __TROPICALL BTP_Tempo:: Objeto()
{

}
//----------------------------------------------------------------------------
int __TROPICALL BTP_Tempo::PegarNumTempo()
{
 return BTP_Tempo::numtempo;
}
//--Propriedades--------------------------------------------------------------
HANDLE __TROPICALL BTP_Tempo::PegarEvento()
{
	return htimer;
}
//---------------------------------------------------------------------------
bool __TROPICALL BTP_Tempo::PegarAtivo()
{
 return ativo;
}
//---------------------------------------------------------------------------
void __TROPICALL BTP_Tempo::AlterarAtivo(bool temp) throw(BTP_Excecao*)
{
 if(temp)
 {
  LARGE_INTEGER Preset;
  Preset.QuadPart=-(intervalo*10000);
  int temp1=0;
  if(!manual)temp1=intervalo;


  if(!SetWaitableTimer(htimer,&Preset,temp1,NULL,NULL,false))
  {
	 throw new BTP_Excecao(this,
			         "Erro iniciar o Temporizador");

  }
  ativo=true;
 }
 else
 {
  if(!CancelWaitableTimer(htimer))
  {
		   throw new BTP_Excecao(this,
					  "Erro ao parar o temporizador");

  }
  ativo=false;
 }
}
//---------------------------------------------------------------------------
float __TROPICALL BTP_Tempo::PegarIntervalo()
{
 return intervalo;
}
//---------------------------------------------------------------------------
void __TROPICALL BTP_Tempo::AlterarIntervalo(float temp) throw(BTP_Excecao*)
{
 intervalo=temp;
 if(ativo)
 {
   LARGE_INTEGER Preset;
   
   Preset.QuadPart=-(intervalo*10000);
   if(!SetWaitableTimer(htimer,&Preset,intervalo,NULL,NULL,false))
   {
		  throw new BTP_Excecao(this,
								"Erro iniciar o Temporizador");

   }
  }
 


}
//---------------------------------------------------------------------------

