#ifndef __dbg_h__
#define __dbg_h__

#include <stdio.h>
#include <errno.h>
#include <string.h>
#define log_function(FLAG,FUNCTION_NAME) FLAG != 1 ? (fprintf(stdout, "|Log of function: "#FUNCTION_NAME  " in file %s on line %d|\n", __FILE__, __LINE__)) : 0
#define log_function_parameter(FLAG,PARAMETER, VALUE, VALUE_SPECIFIER) FLAG != 1 ? (fprintf(stdout, "|Paramater: "#PARAMETER" has value %"#VALUE_SPECIFIER"|\n", VALUE)) : 0
#define log_function_return(FLAG,FUNCTIONA_NAME,RETURN_VALUE, VALUE_SPECIFIER) FLAG != 1 ? (fprintf(stdout, "|Log of function: "#FUNCTIONA_NAME" which returns %"#VALUE_SPECIFIER"|\n", RETURN_VALUE)) : 0
#endif