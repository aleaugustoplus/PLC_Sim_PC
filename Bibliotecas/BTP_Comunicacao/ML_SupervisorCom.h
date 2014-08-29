/*##################################################################
  #             Objeto Supervisor de comunicação com Mini-Lab      #
  #               Copyright©:                                      #
  #                Tropical® Corp.                                 #
  #----------------------------------------------------------------#
  #                   Criada em:                                   #
  #                    26/11/2007 - Alexandre A. S. Lopes          #
  ##################################################################*/
//---------------------------------------------------------------------------

#ifndef ML_SupervisorComH
#define ML_SupervisorComH

#include "BTP_Thread.h"
#include "BTP_Excecao.h"
#include "BTP_Evento.h"




class ML_SupervisorCom:BTP_Thread
{

 public:
 enum SUP_MSG{
			  SUP_ENTRADA,



 };

 private:
 HANDLE hporta;
 char *entrada;
 char *saida;
 char *buffer;
 void AddEntrada(char);
 void AddSaida(char *);
 void ReceberDados();
 unsigned int numentrada;
 void __TROPICALL Executar();
 void __TROPICALL AlterarMascara(unsigned int);




 public:
  ML_SupervisorCom(char*);
  ~ML_SupervisorCom();


  __property char *Entrada = {read=PegarEntrada};
  __property char *Saida = {read=PegarSaida};
  __property HWND JanelaMsg = {write=AlterarJanelaMsg};

  //--Propriedades--------------
  private:
  char * PegarEntrada();
  char * PegarSaida();
  void AlterarJanelaMsg(HWND);

};
//---------------------------------------------------------------------------
#endif
