/*##################################################################
  #           Arquivo de definições de Pré Compilação              #
  #               Copyright©:                                      #
  #                Tropical® Corp.                                 #
  #----------------------------------------------------------------#
  #               Criada em:                                       #
  #               16/08/06 - Alexandre A. S. lopes                 #
  #               Descrição:      							     #
  #           Arquivo de definições de pré-compilação das          #
  #   bibliotecas Tropical.                                        #
  #----------------------------------------------------------------#
  #               Modificada em:                                   #
  #               17/08/2006 - Alexandre A. S. Lopes               #
  #				  06/01/2007 - Alexandre A. S. Lopes               #
  ##################################################################
*/
//Definições de Pré-Compilação


//--Definição de Tipo de Sistema Operacional------------------------------------
#define BTP_MSWIN32
//#define BTP_LINUX

#if defined(BTP_MSWIN32) && defined(BTP_LINUX)
 #error "Dupla definicao de sistema operacional"
#endif

//--Definiçoes do Modo do Programa----------------------------------------------
//#define BTP_CONSOLEAPP
#define BTP_WINDOWAPP

#if defined(BTP_CONSOLEAPP) && defined(BTP_WINDOWAPP)
 #error "Multipla definicao de modo de programa"
#endif

//--Definição de Compilador-----------------------------------------------------
#define BTP_CBUILDER
//#define BTP_DEVCPP
//#define BTP_MSVISUALC

#if defined(BTP_CBUILDER) && defined(BTP_DEVCPP) && defined(BTP_MSVISUALC)
 #error "Multipla definicao de modo de programa"
#endif


//--Definições de Excecao-------------------------------------------------------
#define BTP_EXCECAO
//#define BTP_SEM_EXCECAO


#if defined(BTP_EXCECAO) && defined(BTP_SEM_EXCECAO)
 #error "Dupla definicao de excecao"
#endif


//--Definições de teste---------------------------------------------------------
//#define BTP_TESTE
//--Definição de ligação--------------------------------------------------------
//#define BTP_LINKDINAMICO
#define BTP_LINKESTATICO
//#define BTP_DLLLINK

#if defined(BTP_LINKDINAMICO) && defined(BTP_LINKESTATICO)
 #error "Dupla definicao de ligacao"
#endif
//--Definição de Importação---------------------------------------------------
#ifdef BTP_LINKDINAMICO
 #define BIBTROPICAL __declspec(dllimport)
 #define BTP_EXTERNC extern "C" {
 #define BTP_FIM_EXTERNC }
#endif

#ifdef BTP_LINKESTATICO
 #define BIBTROPICAL
 #define BTP_EXTERNC
 #define BTP_FIM_EXTERNC
#endif

#ifdef BTP_DLLLINK
 #define BIBTROPICAL __declspec(dllexport)
 #define BTP_EXTERNC extern "C" {
 #define BTP_FIM_EXTERNC }
#endif
//--Convenção de chamadas de funções-------------------------------------------
//#define __TROPICALL __cdecl
#define __TROPICALL __fastcall
//#define __TROPICALL __stdcall
//#define __TROPICALL
//--Definições do Microsoft Visual C--BTP_MSVISUALC----------------------------
#ifdef BTP_MSVISUALC
 //#define _WIN32_WINNT  0x0400 //Ativa as novas funções do NT4
 #define _WIN32_WINNT  0x0501 //Ativa as novas funções do WinXP
 //#define _WIN32_WINNT  0x0502 //Ativa as novas funções do Win2003 Server
#endif
//-----------------------------------------------------------------------------
