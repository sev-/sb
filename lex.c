/*
 *  $Id: lex.c,v 1.1 1993/10/09 18:24:27 sev Exp sev $
 *
 * ---------------------------------------------------------- 
 *
 * $Log: lex.c,v $
 * Revision 1.1  1993/10/09  18:24:27  sev
 * Initial revision
 *
 *
 */

/* Разбиение входного потока на лексемы */
 
#include "sb.h"

void find_eol();
void putback();

struct commands 	/* структура ключевых слов анализатора */
{
  char *command;
  char tok;
} table[] =
{
  "print",	PRINT,
  "input",	INPUT,
  "if",		IF,
  "then",	THEN,
  "goto",	GOTO,
  "for",	FOR,
  "next",	NEXT,
  "to",		TO,
  "gosub",	GOSUB,
  "return",	RETURN,
  "end",	END,
  "step",	STEP,
  "",		END
};

look_up(s)	/* поиск соответствия внутреннего формата для текущей */
char *s;	/*   лексемы в таблице лексем */
{
  register int i, j;
  char *p;

  p = s;
  while(*p)
  {
    *p = tolower(*p);
    p++;
  }
  for(i = 0; *table[i].command; i++)
    if(!strcmp(table[i].command, s))
      return (table[i].tok);

  return 0;
}

get_token()		/* чтение лексемы */
{
  register char *temp;

  token_type = 0;
  tok = 0;
  temp = token;

  if(*prog == '\0')	/* конец файла */
  {
    *token = 0;
    tok = FINISHED;
    return (token_type = DELIMITER);
  }
  while(iswhite(*prog))
    prog++;
    
  if(*prog == '\n')	/* конец строки программы */
  {
    prog++;
    tok = EOL;
    *token = '\n';
    token[1] = 0;

    return (token_type = DELIMITER);
  }

  if(*prog == '"')
  {
    prog ++;
    while(*prog != '"' && *prog != '\n')
      *temp++ = *prog++;
    if(*prog == '\n')
      serror(E_BRACKETS);
    *prog++;
    *temp = 0;

    return (token_type = QUOTE);
  }

  if(isdigit(*prog))
  {
    while(!isdelim(*prog))
      *temp++ = *prog++;
    *temp = 0;

    return (token_type = NUMBER);
  }

  if(isalpha(*prog))
  {
    while(!isdelim(*prog))
      *temp++ = *prog++;
    token_type = STRING;
  }

  if(!token_type && isdelim(*prog))		/* (c) SEV */
  {
    *temp++ = *prog++;
    *temp = 0;
    return (token_type = DELIMITER);
  }
  *temp = 0;

  if(token_type == STRING)
  {
    tok = look_up(token);	/* во внутренний формат */
    if(!tok)
      token_type = VARIABLE;
    else
      token_type = COMMAND;
  }

  return (token_type);
}

void putback()		/* бозврат лексемы во входной поток */
{
  char *t;

  t = token;
  for(; *t; t++)
    prog--;
}

isdelim(c)		/* возвращает истину, если c - разделитель */
char c;
{
  if(strchr(" ;,+-<>/*%^=()", c) || c == 9 || c == '\n' || !c)
    return 1;

  return 0;
}

iswhite(c)	/* возвращает истину, если c - пробел или табуляция */
char c;
{
  if(c == ' ' || c == '\t')
    return 1;

  return 0;
}

void find_eol() 	/* Поиск начала следующей строки */
{
  while(*prog != '\n' && *prog != '\0')
    ++prog;
  if(*prog)
    prog++;
}
