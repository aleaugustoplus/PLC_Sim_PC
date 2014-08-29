//---------------------------------------------------------------------------

#ifndef BTP_BufferPortaH
#define BTP_BufferPortaH
//---------------------------------------------------------------------------

#include <windows.h>
#include "BTP_Objeto.h"
#include "BTP_Evento.h"


#define TAMANHO_BUFFER_STR   100

class BTP_BufferPorta:public BTP_Objeto
{

  BTP_Evento *evSaida;
  void __TROPICALL Objeto();
  char        entrada[30];
  char        bufferstr[TAMANHO_BUFFER_STR];
  OVERLAPPED  ovsaida;
  OVERLAPPED  ovIn;
  HANDLE  Porta;
  friend class BTP_PortaSerial;
  unsigned int  tamanhobufferstr;


 public:
         
  BTP_BufferPorta(char*,HANDLE porta);
  ~BTP_BufferPorta();

  void AddInBufferStr();
  void LimparBufferStr();


  __property HANDLE hPorta = {read=PegarhPorta};
  __property char Entrada = {read=PegarEntrada};
  __property char*BufferStr ={read = PegarBufferStr};


  HANDLE PegarhPorta();
  char PegarEntrada();
  char *PegarBufferStr();
};

#endif
