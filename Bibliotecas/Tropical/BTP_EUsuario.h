/*##################################################################
  #                  Objeto Exce��o do Usuario                     #
  #               Copyright�:                                      #
  #                Tropical� Corp.                                 #
  #----------------------------------------------------------------#
  #               Criada em:                                       #
  #               16/07/06 - Alexandre A. S. lopes                 #
  #               Descri��o:                                       #
  #                Classe de tratamento de exce��es do usuario     #
  #          faz a interface dos erros de hardware com o usu�rio   #
  ##################################################################*/
//---------------------------------------------------------------------------

#ifndef BTP_EUsuarioH
#define BTP_EUsuarioH
#include "BTP_Excecao.h"

class BIBTROPICAL BTP_EUsuario: public BTP_Excecao
{
 public:
  enum TipoDeExcecao {ERRO,
  AVISO};

 private:
   TipoDeExcecao tipo;
 public:
   __TROPICALL BTP_EUsuario(BTP_Objeto*,TipoDeExcecao,char *tmsgtxt);
 };
//---------------------------------------------------------------------------
#endif
