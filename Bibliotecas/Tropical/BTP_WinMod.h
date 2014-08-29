/*##################################################################
  #                Objeto de modificações do windows               #
  #               Copyright©:                                      #
  #                Tropical® Corp.                                 #
  #----------------------------------------------------------------#
  #               Criada em:                                       #
  #               18/10/06 - Alexandre A. S. lopes                 #
  #               Descrição:                                       #
  #             Classe que altera configurações do windows         #
  ##################################################################*/
//---------------------------------------------------------------------------
#pragma region Declarações de cabeçalho

#ifndef BTP_WinModH
 #define BTP_WinModH

 #include "BTP_Objeto.h"
 #include <windows.h>
 #include <iostream>




 class  BIBTROPICAL  BTP_WinMod: BTP_Objeto
 {
  void __TROPICALL Objeto();
  public:
   __TROPICALL BTP_WinMod(char* nome="Modifcador");
   __TROPICALL ~BTP_WinMod(void);
  void __TROPICALL EscondeIni(bool);
  void __TROPICALL EscondeDesk(bool);
  void __TROPICALL EscondeBar(bool);
  void __TROPICALL Desligar(void);
  void __TROPICALL LabelIni(wchar_t*);
  void __TROPICALL EscondeRelog(bool);
 };

//---------------------------------------------------------------------------
#endif
