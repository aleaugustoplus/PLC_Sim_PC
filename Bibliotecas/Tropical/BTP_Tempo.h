/*##################################################################
  #                    Objeto Temporizador                         #
  #               Copyright©:                                      #
  #                Tropical® Corp.                                 #
  #----------------------------------------------------------------#
  #               Criada em:                                       #
  #               27/06/06 - Alexandre A. S. lopes                 #
  #               Descrição:                                       #
  #               Classe de temporização que dispara um evento     #
  #        quando é esgotado o tempo limite.                       #
  #        Esta Classe ultiliza um WaitableTimer                   #
  #--Observações---------------------------------------------------#
  # bool ativarmanual                                              #
  # Reset Manual- O evento é disparado e fica no estado sinalizado #
  # acordando todas as threads até que volte a sinalizar Reset o   #
  # novamente.                                                     #
  # Reset Automático - O evento é sinalizado logo depois não       #
  # sinalizado apenas uma thread será acordada e o evento voltará  #
  #	para o estado não-sinalizado.                              #
  ##################################################################
*/
//---------------------------------------------------------------------------
#ifndef BTP_TempoH
#define BTP_TempoH


#include <windows.h>
#include <string.h>
#include "BTP_Objeto.h"
#include "BTP_Excecao.h"




class BIBTROPICAL BTP_Tempo :public BTP_Objeto
{
  HANDLE htimer;
  bool manual;

  bool ativo;
  void  __TROPICALL Objeto();

  
  float intervalo;
  static int numtempo;
  public:

   __TROPICALL BTP_Tempo(char *,bool ativarmanual=false)throw(BTP_Excecao*);
   __TROPICALL ~BTP_Tempo();

  static int __TROPICALL PegarNumTempo();

  #ifdef BTP_CBUILDER
  __property HANDLE hEvento= {read=PegarEvento};
  __property bool Ativo={read=PegarAtivo,write=AlterarAtivo};
  __property float Intervalo={read=PegarIntervalo,write=AlterarIntervalo};//Intervalo em
																		//Milisegundos
  //--Funções das propriedades  
  private:  
  #endif

  HANDLE __TROPICALL PegarEvento();
  bool   __TROPICALL PegarAtivo();
  void   __TROPICALL AlterarAtivo(bool)throw(BTP_Excecao*);
  float    __TROPICALL PegarIntervalo();
  void   __TROPICALL AlterarIntervalo(float)throw(BTP_Excecao*);
};




//---------------------------------------------------------------------------
#endif
