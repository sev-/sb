/*
 *  $Id: input.c,v 1.1 1993/10/09 18:24:27 sev Exp sev $
 *
 * ---------------------------------------------------------- 
 *
 * $Log: input.c,v $
 * Revision 1.1  1993/10/09  18:24:27  sev
 * Initial revision
 *
 *
 */
 
/* ввод с клавиатуры */
#include "sb.h"

void input()		/* Реализация оператора INPUT */
{
  char str[80], var;
  int i;

  get_token();	/* Просматривается ели цуществует строка символов */

  if(token_type == QUOTE)
  {
    printf(token); /* Если да, то ее печать и контроль */
    get_token();

    if(*token != ',')
      serror(E_BRACKETS);

    get_token();
  }
  else
    printf("? ");		/* Выдача строки по умолчанию */

  var = toupper(*token) - 'A';	/* Получить адрес имени переменной */
  scanf("%d", &i);		/* Чтение ввода данных */
  variables[var] = i;		/* Сохранение данных */
}
