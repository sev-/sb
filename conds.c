/*
 *  $Id: conds.c,v 1.1 1993/10/09 18:24:27 sev Exp sev $
 *
 * ---------------------------------------------------------- 
 *
 * $Log: conds.c,v $
 * Revision 1.1  1993/10/09  18:24:27  sev
 * Initial revision
 *
 *
 */

/* Условия */
#include "sb.h"

void exec_if()		/* Реализация оператора IF */
{
  int x, y, cond;
  char op;

  get_exp(&x);		/* Получить левое выражение */
  get_token();		/* Получить оператор */

  if(!strchr("=<>", *token))
  {
    serror(E_SYNTAX);
    return;
  }

  op = *token;
  get_exp(&y);		/* Получить правое выражение */

  /* Определение результата */
  cond = 0;
  switch(op)
  {
    case '=':
	if(x == y)
	  cond = 1;
	break;
    case '<':
	if(x < y)
	  cond = 1;
	break;
    case '>':
	if(x > y)
	  cond = 1;
	break;
  }

  if(cond)
  {
    get_token();
    if(tok != THEN)
    {
      serror(E_NEEDTHEN);
      return;
    }	  /* Иначе программа выполняетса со следующей строки */
  }
  else
    find_eol(); 		/* Поиск точки старта программы */
}
