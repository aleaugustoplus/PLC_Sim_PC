/*##################################################################
  #                       Objeto Evento                            #
  #               Copyright©:                                      #
  #                Tropical® Corp.                                 #
  #----------------------------------------------------------------#
  #               Modificada em:                                   #
  #               16/07/2006 - Alexandre A. S. lopes               #
  #              Mudança no sistema de exceções                    #
  ##################################################################*/

//---------------------------------------------------------------------------
#include "BTP_Evento.h"
//---------------------------------------------------------------------------
__TROPICALL BTP_Evento::BTP_Evento(char* nome,bool ativarmanual,bool estadoinicial)throw(BTP_Excecao*):BTP_Objeto(nome)
{
	hevento=CreateEventA(NULL, ativarmanual, estadoinicial,nome);
	ativo=estadoinicial;
	if(!hevento)
	{
		  throw new BTP_Excecao(this,
					"Erro ao tentar criar o Evento");

	}
}
//---------------------------------------------------------------------------
__TROPICALL BTP_Evento::~BTP_Evento()
{
 CloseHandle(hevento);
}
//---------------------------------------------------------------------------
void   __TROPICALL BTP_Evento::Objeto()
{

}
//---------------------------------------------------------------------------
void   __TROPICALL BTP_Evento::PulsarEvento() throw(BTP_Excecao*)
{
 if(!PulseEvent(hevento))
 {
  throw new BTP_Excecao(this,
						"Erro ao tentar pulsar o Evento");
 }
}
//--Propriedades-------------------------------------------------------------
HANDLE __TROPICALL BTP_Evento::PegarEvento()
{
 return hevento;
}
//---------------------------------------------------------------------------
bool   __TROPICALL BTP_Evento::PegarAtivo()
{
 return ativo;
}
//---------------------------------------------------------------------------
void   __TROPICALL BTP_Evento::AlterarAtivo(bool temp)throw(BTP_Excecao*)
{
 if (temp)
 {
  ativo=true;
  if(!SetEvent(hevento))
  {
	throw new BTP_Excecao(this,
			      "Erro ao tentar Sinalizar Evento");
  }

 }
 else
 {
  ativo=false;
  if(!ResetEvent(hevento))
  {
	 throw new BTP_Excecao(this,
			       "Erro ao tentar tirar o evento do estado sinalizado");
  }
 }
}
//---------------------------------------------------------------------------
