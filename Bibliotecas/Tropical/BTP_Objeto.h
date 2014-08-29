/*##################################################################
  #                       Objeto Pai                               #
  #               Copyright©:                                      #
  #                Tropical® Corp.                                 #
  ##################################################################
*/

//---------------------------------------------------------------------------
#ifndef BTP_ObjetoH
#define BTP_ObjetoH
#include "BTP_PreConfig.h"

#include <iostream>

		   
class BIBTROPICAL BTP_Objeto
{

    char *nome;
	virtual void  __TROPICALL Objeto()=0;

 public:
 __TROPICALL  BTP_Objeto(char* tnome);
 __TROPICALL  ~BTP_Objeto();


 #ifdef BTP_CBUILDER
  __property char* Nome={read=PegarNome};

  protected:
  __property char *MudaNome={write=AlterarMudaNome};
  private:
 #endif
  char* __TROPICALL PegarNome();

  protected:
  void __TROPICALL AlterarMudaNome (char*);



};



//---------------------------------------------------------------------------
#endif
