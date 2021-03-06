/*##################################################################
  #           Arquivo de defini��es de Pr� Compila��o              #
  #               Copyright�:                                      #
  #                Tropical� Corp.                                 #
  #----------------------------------------------------------------#
  #               Criada em:                                       #
  #               16/08/06 - Alexandre A. S. lopes                 #
  #               Descri��o:      							     #
  #           Arquivo de defini��es de pr�-compila��o das          #
  #   bibliotecas Tropical.                                        #
  #----------------------------------------------------------------#
  #               Modificada em:                                   #
  #               17/08/2006 - Alexandre A. S. Lopes               #
  #				  06/01/2007 - Alexandre A. S. Lopes               #
  ##################################################################
*/
//Defini��es de Pr�-Compila��o


//--Defini��o de Tipo de Sistema Operacional------------------------------------
#define BTP_MSWIN32
//#define BTP_LINUX

#if defined(BTP_MSWIN32) && defined(BTP_LINUX)
 #error "Dupla definicao de sistema operacional"
#endif

//--Defini�oes do Modo do Programa----------------------------------------------
//#define BTP_CONSOLEAPP
#define BTP_WINDOWAPP

#if defined(BTP_CONSOLEAPP) && defined(BTP_WINDOWAPP)
 #error "Multipla definicao de modo de programa"
#endif

//--Defini��o de Compilador-----------------------------------------------------
#define BTP_CBUILDER
//#define BTP_DEVCPP
//#define BTP_MSVISUALC

#if defined(BTP_CBUILDER) && defined(BTP_DEVCPP) && defined(BTP_MSVISUALC)
 #error "Multipla definicao de modo de programa"
#endif


//--Defini��es de Excecao-------------------------------------------------------
#define BTP_EXCECAO
//#define BTP_SEM_EXCECAO


#if defined(BTP_EXCECAO) && defined(BTP_SEM_EXCECAO)
 #error "Dupla definicao de excecao"
#endif


//--Defini��es de teste---------------------------------------------------------
//#define BTP_TESTE
//--Defini��o de liga��o--------------------------------------------------------
//#define BTP_LINKDINAMICO
#define BTP_LINKESTATICO
//#define BTP_DLLLINK

#if defined(BTP_LINKDINAMICO) && defined(BTP_LINKESTATICO)
 #error "Dupla definicao de ligacao"
#endif
//--Defini��o de Importa��o---------------------------------------------------
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
//--Conven��o de chamadas de fun��es-------------------------------------------
//#define __TROPICALL __cdecl
#define __TROPICALL __fastcall
//#define __TROPICALL __stdcall
//#define __TROPICALL
//--Defini��es do Microsoft Visual C--BTP_MSVISUALC----------------------------
#ifdef BTP_MSVISUALC
 //#define _WIN32_WINNT  0x0400 //Ativa as novas fun��es do NT4
 #define _WIN32_WINNT  0x0501 //Ativa as novas fun��es do WinXP
 //#define _WIN32_WINNT  0x0502 //Ativa as novas fun��es do Win2003 Server
#endif
//-----------------------------------------------------------------------------
