//---------------------------------------------------------------------------

#ifndef BTP_SerialWorksH
#define BTP_SerialWorksH


#include "BTP_Thread.h"
#include "BTP_CompletionPort.h"


class SerialWorks:public BTP_Thread
{
 BTP_CompletionPort *CompletionPort;

 void __TROPICALL Executar();

 public:
  SerialWorks(char*,BTP_CompletionPort*);
  ~SerialWorks();


};
//---------------------------------------------------------------------------
#endif
