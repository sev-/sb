/*
 *  $Id: vars.c,v 1.1 1993/10/09 18:24:27 sev Exp sev $
 *
 * ---------------------------------------------------------- 
 *
 * $Log: vars.c,v $
 * Revision 1.1  1993/10/09  18:24:27  sev
 * Initial revision
 *
 *
 */
 
/* присваивание, нижний уровень переменных */
#include "sb.h"

assignment()		/* Присваивание значения переменной */
{
  int var, value;

  get_token();
  if(!isalpha(*token))
  {
    serror(E_NEEDVAR);	/* Не переменная */
    return;
  }

  /* Вычисление индекса переменной */
  var = toupper(*token) - 'A';

  /* Получить знак равенства */
  get_token();
  if(*token != '=')
  {
    serror(E_NEEDEQU);
    return;
  }

  /* Получить значение, присваиваемое переменной */
  get_exp(&value);

  /* Присвоить это значение */
  variables[var] = value;
}

int find_var(s) 	/* Поиск значения переменной */
char *s;
{
  if(!isalpha(*s))
  {
    serror(E_NEEDVAR);	/* Не переменная */
    return 0;
  }
  return variables[toupper(*token)-'A'];
}
