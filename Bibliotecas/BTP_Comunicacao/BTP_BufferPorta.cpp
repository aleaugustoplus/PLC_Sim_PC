//---------------------------------------------------------------------------


#include "BTP_BufferPorta.h"
#include <stdio.h>
//---------------------------------------------------------------------------
BTP_BufferPorta::BTP_BufferPorta(char*nome,HANDLE porta):BTP_Objeto(nome)
{
   evSaida= new BTP_Evento("Evento Overlapped saida");
   Porta=porta;

   ovsaida.hEvent = evSaida->hEvento;
   ovsaida.hEvent = (HANDLE)((DWORD)  ovsaida.hEvent | 0x1);

   this->LimparBufferStr();


}
//---------------------------------------------------------------------------
BTP_BufferPorta::~BTP_BufferPorta()
{
 delete evSaida;
}
//---------------------------------------------------------------------------
void __TROPICALL BTP_BufferPorta::Objeto()
{

}
//---------------------------------------------------------------------------
void BTP_BufferPorta::AddInBufferStr()
{
  bufferstr[tamanhobufferstr]=entrada[0];
  tamanhobufferstr++;
}
//---------------------------------------------------------------------------
void BTP_BufferPorta::LimparBufferStr()
{
 for(int x=0;x<TAMANHO_BUFFER_STR;x++)
  bufferstr[x]='\0';


 tamanhobufferstr=0;
}
//---------------------------------------------------------------------------
HANDLE BTP_BufferPorta::PegarhPorta()
{
  return Porta;
}
//---------------------------------------------------------------------------
char BTP_BufferPorta::PegarEntrada()
{
 return entrada[0];
}
//---------------------------------------------------------------------------
char *BTP_BufferPorta::PegarBufferStr()
{
 return bufferstr;
}
//---------------------------------------------------------------------------
