/*
 *  $Id: loops.c,v 1.1 1993/10/09 18:24:27 sev Exp sev $
 *
 * ---------------------------------------------------------- 
 *
 * $Log: loops.c,v $
 * Revision 1.1  1993/10/09  18:24:27  sev
 * Initial revision
 *
 *
 */

/* циклы */
 
#include "sb.h"

struct for_stack
{
  int var;	/* счетчик */
  int target;	/* конечноле значение */
  int step;	/* шаг */
  char *loc;
} fstack[FOR_NEST];	/* stack for-next */

struct for_stack fpop();
void fpush();
 
void exec_for() 	/* Реализация цикла FOR */
{
  struct for_stack i;
  int value;
  int nesting;

  get_token();			/* Получить управляющую переменную */

  if(!isalpha(*token))
  {
    serror(E_NEEDVAR);
    return;
  }

  i.var = toupper(*token) - 'A';	/* Сохранить индекс */

  get_token();			/* Получить знак равенства */

  if(*token != '=')
  {
    serror(E_NEEDEQU);
    return;
  }

  get_exp(&value);		/* Получить началтное значение */
  variables[i.var] = value;

  get_token();
  if(tok != TO)
    serror(E_NEEDTO);		/* Если не нашли TO */
  get_exp(&i.target);		/* Получить конечное значение */

  get_token();		/* (c) SEV */
  if(tok != STEP)	/* если шага нет, возвратим лексему */
  {
    i.step = 1;		/* шаг по умолчанию - +1 */
    putback();
  }
  else
  {
    get_exp(&i.step);		/* взять числовое значение шага */
    if(!i.step)
      serror(E_BADSTEP);	/* шаг не должен быть 0 ! */
  }
    

  /* Если цикл выполняется последний раз, поместить
    информацию в стек */  	
  if(value <= i.target)
  {
    i.loc = prog;
    fpush(i);
  }
  else				/* Пропустить весь цикл */
  {			/* (c) SEV */
    nesting = 1;
    while(nesting)
    {
      get_token();
      if(tok == NEXT)
	nesting --;
      else
	if(tok == FOR)
	  nesting++;
    }
  }
}

void next()		/* Реaлизация оператора NEXT */
{
  struct for_stack i;

  i = fpop();			/* Чтение информации о цикле */

  variables[i.var] += i.step;	/* Увеличение управляющей переменной */

  if(variables[i.var] > i.target)
    return;

  fpush(i);			/* Иначе сохранить информацию о стеке */
  prog = i.loc;		/* Цикл */
}

void fpush(i)		/* Поместить информацию в стек FOR */
struct for_stack i;
{
  if(ftos > FOR_NEST)
    serror(E_TOOFOR);

  fstack[ftos] = i;
  ftos++;
}

struct for_stack fpop()
{
  ftos--;

  if(ftos < 0)
    serror(E_BADNEXT);

  return (fstack[ftos]);
}

