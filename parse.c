/*
 *  $Id: parse.c,v 1.1 1993/10/09 18:24:27 sev Exp sev $
 *
 * ---------------------------------------------------------- 
 *
 * $Log: parse.c,v $
 * Revision 1.1  1993/10/09  18:24:27  sev
 * Initial revision
 *
 *
 */

/* синтаксический разбор входного потока */ 

#include "sb.h"

void level2();
void level3();
void level4();
void level5();
void level6();
void primitive();
void arith();
void unary();


void get_exp(result)		/* Точка входа в лексический анализатор */
int *result;
{
  get_token();

  if(!*token)
  {
    serror(E_BADEXP);
    return;
  }

  level2(result);
  putback();	/* Возвращает последнюю считаную лексему обратно в поток */
}

void level2(result)		/* Сложение или вычитание двух термов */
int *result;
{
  register char op;
  int hold;

  level3(result);

  while((op = *token) == '+' || op == '-')
  {
    get_token();
    level3(&hold);
    arith(op,result,&hold);
  }
}

void level3(result)  /* Вычисление произведения или частного двух факторов */
int *result;
{
  register char op;
  int hold;

  level4(result);

  while((op = *token) == '*' || op =='/' || op == '%')
  {
    get_token();
    level4(&hold);
    arith(op, result, &hold);
  }
}

void level4(result)	/* Обработка степени числа (целочисленной) */
int *result;
{
  int hold;

  level5(result);

  if(*token == '^')
  {
    get_token();
    level4(&hold);
    arith('^', result, &hold);
  }
}

void level5(result)	/* Унарный + или - */
int *result;
{
  register char op;

  op = 0;
  if((token_type == DELIMITER) && *token == '+' || *token == '-')
  {
    op = *token;
    get_token();
  }

  level6(result);

  if(op)
    unary(op, result);
}

void level6(result)	/* Обработка выражения в круглыь скобках */
int *result;
{
  if((*token == '(') && (token_type == DELIMITER))
  {
    get_token();

    level2(result);

    if(*token != ')')
      serror(E_BRACKETS);
    get_token();
   }
   else
     primitive(result);
}

void primitive(result)	/* Опредиление значения переменной */
int *result;
{
  switch(token_type)
  {
    case VARIABLE:
      *result = find_var(token);
      get_token();
      return;
    case NUMBER:
      *result = atoi(token);
      get_token();
      return;
    default:
      serror(E_SYNTAX);
  }
}

void arith(op, r, h)	/* Выполнение специицированной арифметики */
char op;
int *r, *h;
{
  register int t, ex;

  switch(op)
  {
    case '-':
      *r = *r-*h;
      break;
    case '+':
      *r = *r+*h;
      break;
    case '*':
      *r = *r * *h;
      break;
    case '/':
      *r = (*r)/(*h);
      break;
    case '%':
      t = (*r)/(*h);
      *r = *r-(t*(*h));
      break;
    case '^':
      ex = *r;
      if(*h == 0)
      {
	*r = 1;
	break;
      }
      for(t = *h-1; t > 0; --t)
	*r = (*r) * ex;
      break;
  }
}

void unary(op, r)	/* Унарные операции */
char op;
int *r;
{
  if(op == '-')
    *r = -(*r);
}
