//$$---- Form HDR ----
//---------------------------------------------------------------------------

#ifndef uPrinicpalH
#define uPrinicpalH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "PLC_Controle.h"
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TfPrincipal : public TForm
{
__published:	// IDE-managed Components
	TTimer *Timer1;
	TCheckBox *ckbEnt0;
	TCheckBox *ckbEnt1;
	TCheckBox *ckbEnt2;
	TCheckBox *ckbEnt3;
	TCheckBox *ckbSaida3;
	TCheckBox *ckbSaida2;
	TCheckBox *ckbSaida1;
	TCheckBox *ckbSaida0;
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall ckbSaida0Click(TObject *Sender);
private:	// User declarations
	TCheckBox *ckbEnts[4];
    TCheckBox *ckbSaidas[4];
	PLC_Controle *Controle;
public:		// User declarations
	__fastcall TfPrincipal(TComponent* Owner);
	__fastcall ~TfPrincipal();
};
//---------------------------------------------------------------------------
extern PACKAGE TfPrincipal *fPrincipal;
//---------------------------------------------------------------------------
#endif
