/*
 *  $Id: print.c,v 1.1 1993/10/09 18:24:27 sev Exp sev $
 *
 * ---------------------------------------------------------- 
 *
 * $Log: print.c,v $
 * Revision 1.1  1993/10/09  18:24:27  sev
 * Initial revision
 *
 *
 */
 
/* вывод на экран */
#include "sb.h"

void print()		/* Простейшая реализация оператора PRINT */
{
  int answer;
  int len = 0, spaces;
  char last_delim;

  do
  {
    get_token();
    if(tok == EOL || tok == FINISHED)
      break;
    if(token_type == QUOTE) /* Это строка */
    {
      printf(token);
      len += strlen(token);
      get_token();
    }
    else /* Это выражение */
    {
      putback();
      get_exp(&answer);
      get_token();
      len += printf("%d", answer);
    }
    last_delim = *token;

    if(*token == ',')	/* Вычисление числа пробелов при пееходе к */
    {				 /* следующей табуляции */	
      spaces = 8 - (len % 8);
      len += spaces;	/* Включая поз. табуляции */
      while(spaces)
      {
	printf(" ");
	spaces--;
      }
    }
    else
      if(*token == ';');	/* ничего не делать */
      else
	if(tok != EOL && tok != FINISHED)
	  serror(E_SYNTAX);
  } while (*token == ';' || *token == ',');

  if(tok == EOL || tok == FINISHED)
  {
    if(last_delim != ';' && last_delim != ',')
      printf("\n");
  }
  else
    serror(E_SYNTAX);		/* Отсутствует ';' or ',' */
}
