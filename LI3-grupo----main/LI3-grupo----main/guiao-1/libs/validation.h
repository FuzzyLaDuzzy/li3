/*
Módulo com funções partilhadas 
de validação de campos de entrada 
*/
#ifndef VALIDATE_SHRD
#define VALIDATE_SHRD

#define _GNU_SOURCE

#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>

/*
devolve uma cópia (uma string) do token entre dois delimitadores
*/
char* cpStr (char** line);

/* retorna true para datas entre 
	2005/04/07 - 00:00:00  
	e
	2021/11/07 - 23:59:00 
*/
bool validDate (struct tm date);

/*
retorna true para strings não vazias e de carateres numéricos não negativos       
*/

bool validNonNegativeDigit (char * line);

/*
	converte input de string dado: eg."True" ou "False" 
	nos respectivos tipos booleanos true e false
*/
bool string2bool (char* x);

/*
	converte input booleano em string respectiva:
	true -> "True" ou false -> "False"
*/
char* bool2string (bool x);

#endif