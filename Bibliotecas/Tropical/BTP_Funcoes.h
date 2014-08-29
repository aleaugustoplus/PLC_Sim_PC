/*##################################################################
  #                    Namespace Tropical                          #
  #               Copyright�:                                      #
  #                Tropical� Corp.                                 #
  #----------------------------------------------------------------#
  #               Criada em:                                       #
  #               29/06/06 - Alexandre A. S. lopes                 #
  #               Descri��o:                                       #
  #               Fun��es e estruturas da Tropical� Corp.          #
  #----------------------------------------------------------------#
  #               Modificada em:                                   #
  #               17/07/06 - Alexandre O. Santos	               #
  #----------------------------------------------------------------#
  #               Modificada em:                                   #
  #               23/07/06 - Alexandre O. Santos	               #
  #      Adicionado fun��o IntToUint(int) que retorna sempre um    #
  #    valor positivo de um inteiro.                               #
  #----------------------------------------------------------------#
  ##################################################################
*/

//---------------------------------------------------------------------------
#ifndef BTP_FuncoesH
#define BTP_FuncoesH
#include "BTP_PreConfig.h"
//-----Estruturas--------------------------
//--Abstra��o do papel fotogr�fico--
typedef struct BTP_Papel
		 {
		   int Topo;
		   int Esquerda;
		   int Largura;
		   int Altura;
		  }TP_Papel,TP_lPapel;
//--Mapeamento de cores de imagem------
typedef struct BTP_ImagemBMP
		 {
		  int Red;
		  int Green;
		  int Blue;

		 }TP_Imagem;
//--Byte de dados----------------------
//typedef unsigned char Byte;

// Fun��o que retorna um valor sempre positivo de um inteiro --
BIBTROPICAL unsigned int __TROPICALL IntToUint(int);
//-------------------------------------------------------------

//-------------------------------------------------------------------


//---------------------------------------------------------------------------
#endif
