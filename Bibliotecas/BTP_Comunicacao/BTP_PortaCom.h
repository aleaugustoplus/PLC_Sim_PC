/*##################################################################
  #                Objeto de Comunicação                           #
  #               Copyright©:                                      #
  #                Tropical® Corp.                                 #
  #----------------------------------------------------------------#
  #               Criada em:                                       #
  #               12/07/07 - Alexandre A. S. Lopes                 #
  #               Descrição:                                       #
  #               Classe de controle de comunicação                #
  ##################################################################*/

//---------------------------------------------------------------------------

#ifndef BTP_PortaComH
#define BTP_PortaComH

#include "BTP_Objeto.h"

#include "ML_TransmissaoConfig.h"



class BIBML_TRANSMISSAO BTP_PortaCom :public BTP_Objeto
{
public:
 typedef unsigned char Dado;
private:
 void __TROPICALL Objeto();

public:

__TROPICALL BTP_PortaCom(char*);
__TROPICALL ~BTP_PortaCom();

 virtual void __TROPICALL TransmitirByte(Dado Buffer)=0;
 virtual Dado __TROPICALL ReceberByte()=0;

 };

//---------------------------------------------------------------------------
#endif
