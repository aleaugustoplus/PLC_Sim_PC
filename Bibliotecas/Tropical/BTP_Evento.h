/*##################################################################
  #                       Objeto Evento                            #
  #               Copyright�:                                      #
  #                Tropical� Corp.                                 #
  #----------------------------------------------------------------#
  #               Criada em:                                       #
  #               29/06/06 - Alexandre A. S. lopes                 #
  #               Descri��o:                                       #
  #               Objeto de evento do sistema operacional! sinaliza#
  #  um evento para uma thread que esteja esperenda por ele        #
  #--Observa��es---------------------------------------------------#
  # bool ativarmanual                                              #
  # Reset Manual- O evento � disparado e fica no estado sinalizado #
  # acordando todas as threads at� que volte a sinalizar Reset o   #
  # novamente.                                                     #
  # Reset Autom�tico - O evento � sinalizado logo depois n�o       #
  # sinalizado apenas uma thread ser� acordada e o evento voltar�  #
  #	para o estado n�o-sinalizado Se nenhuma thread estiver esperan-#
  #	do pelo evento naquele instante, ent�o o evento � perdido.     #
  ##################################################################
*/
//---------------------------------------------------------------------------
#ifndef BTP_EventoH
#define BTP_EventoH
#include<Process.h>
#include<windows.h>
#include "BTP_Objeto.h"
#include "BTP_Excecao.h"


class BIBTROPICAL BTP_Evento: public BTP_Objeto
{
  HANDLE hevento;
  bool ativo;

  void  __TROPICALL Objeto();

  public:

    __TROPICALL BTP_Evento(char*,bool ativarmanual=false,bool estadoinicial=false) throw(BTP_Excecao*);
    __TROPICALL ~BTP_Evento();
  void __TROPICALL PulsarEvento() throw(BTP_Excecao*);

  #ifdef BTP_CBUILDER
   __property HANDLE hEvento={read=PegarEvento};
   __property bool Ativo={read=PegarAtivo,write=AlterarAtivo};


  //Propriedades
   private:
  #endif

  HANDLE __TROPICALL PegarEvento();
  bool   __TROPICALL PegarAtivo();
  void   __TROPICALL AlterarAtivo(bool) throw(BTP_Excecao*);

};
//---------------------------------------------------------------------------
#endif
