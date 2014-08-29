/*##################################################################
  #                Objeto de modifica��es do windows               #
  #               Copyright�:                                      #
  #                Tropical� Corp.                                 #
  #----------------------------------------------------------------#
  #               Criada em:                                       #
  #               18/10/06 - Alexandre A. S. lopes                 #
  #               Descri��o:                                       #
  #             Classe que altera configura��es do windows         #
  ##################################################################*/
//---------------------------------------------------------------------------
#pragma region Declara��es de cabe�alho

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
