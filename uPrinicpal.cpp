//$$---- Form CPP ----
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uPrinicpal.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfPrincipal *fPrincipal;
//---------------------------------------------------------------------------
__fastcall TfPrincipal::TfPrincipal(TComponent* Owner)
	: TForm(Owner)
{
 Controle=new PLC_Controle("Controlador de PLC");
 Timer1->Enabled=true;

 ckbEnts[0] = ckbEnt0;
 ckbEnts[1] = ckbEnt1;
 ckbEnts[2] = ckbEnt2;
 ckbEnts[3] = ckbEnt3;

 ckbSaidas[0] = ckbSaida0;
 ckbSaidas[1] = ckbSaida1;
 ckbSaidas[2] = ckbSaida2;
 ckbSaidas[3] = ckbSaida3;
}
//---------------------------------------------------------------------------

__fastcall TfPrincipal::~TfPrincipal()
{
 delete Controle;
}
//---------------------------------------------------------------------------
void __fastcall TfPrincipal::Timer1Timer(TObject *Sender)
{
 for(int x=0;x<4;x++)
  ckbEnts[x]->Checked = Controle->EntradasDigitais[x];
}
//---------------------------------------------------------------------------
void __fastcall TfPrincipal::ckbSaida0Click(TObject *Sender)
{
 for(int x=0;x<4;x++)
  if(Sender == ckbSaidas[x])
   Controle->SaidasDigitais[x] = ckbSaidas[x]->Checked;
}
//---------------------------------------------------------------------------
