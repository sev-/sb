/*
 *  $Id: go.c,v 1.1 1993/10/09 18:24:27 sev Exp sev $
 *
 * ---------------------------------------------------------- 
 *
 * $Log: go.c,v $
 * Revision 1.1  1993/10/09  18:24:27  sev
 * Initial revision
 *
 *
 */

/* Переходы */

#include "sb.h"

char *gpop();
void gpush();
void scan_labels();
char *find_label();
void label_init();

char *gstack[SUB_NEST]; /* gosub stack */

struct label
{
  char name[LAB_LEN];
  char *p;
};

struct label label_table[NUM_LAB];

void gosub()		/* Реализация оператора GOSUB */
{
  char *loc;

  get_token();

  /* Поиск метки вызова */
  loc = find_label(token);

  if(loc == '\0')
    serror(E_NOLABEL);		 /* Метка не определина */
  else
  {
    gpush(prog);		/* Запомним место, куда вернемся */
    prog = loc;			/* Старт программы с указанной точки */
  }
}

void greturn()		/* Возврат */
{
  prog = gpop();
}

void gpush(s)		/* Помещает данные в стэк */
char *s;
{
  gtos++;
  if(gtos == SUB_NEST)
  {
    serror(E_TOOGOSUB);
    return;
  }
  gstack[gtos] = s;
}

char *gpop()		/* Извлечь данные из стэка подпрограмм */
{
  if(gtos == 0)
  {
    serror(E_BADRETURN);
    return;
  }

  return (gstack[gtos--]);
}


void exec_goto()		/* Реализация оператора GOTO */
{
  char *loc;

  get_token();		/* Получить метку перехода */

  /* Поиск местоположения метки */
  loc = find_label(token);

  if(loc == '\0')
    serror(E_NOLABEL);	 /* Метка не обнаружена */
  else
    prog = loc; 	/* Старт программы с указанной точки */
}

void scan_labels()		/* Поиск всех меток */
{
  int addr;
  char *temp;

  label_init(); 	/* Обнуление всех меток */
  temp = prog;		/* Сохраним указатель на начало программы */

  /* Если первая лексема программы есть метка */
  get_token();
  if(token_type == NUMBER)
  {
    strcpy(label_table[0].name, token);
    label_table[0].p = prog;
  }

  find_eol();
  do
  {
    get_token();
    if(token_type == NUMBER)
    {
      addr = get_next_label(token);
      if(addr == -1 || addr == -2)
      {
	(addr == -1) ? serror(E_TOOLABELS) : serror(E_DUPLABELS);
      }
      strcpy(label_table[addr].name, token);
      label_table[addr].p = prog;	/* Текущий указатель программы */
    }
    /* Если строка не помечена, то поиск следуюшей */
    if(tok != EOL)
    find_eol();
  } while(tok != FINISHED);

  prog = temp;			/* Сохраним оригинал */
}

/* Возвращает индекс на следующую свободную позицию
   массива меток.  -1, если массив переполн		   -2, если дублирование меток. */

get_next_label(s)
char *s;
{
  register int t;

  for(t = 0; t < NUM_LAB; ++t)
  {
    if(label_table[t].name[0] == 0)
      return t;
    if(!strcmp(label_table[t].name,s))
      return -2;		/* Дубль */
  }
  return -1;
}

/* Поиск строки по известной метке. Значение 0 возвращается,
   если метка не найдена; в протибном случае возвращается
   указатель на помеченую строку программы */

char *find_label(s)
char *s;
{
  register int t;

  for(t=0; t < NUM_LAB; ++t)	   
    if(!strcmp(label_table[t].name, s))
      return label_table[t].p;

  return '\0';		/* Состояние ошибки */
}

/* Инициализация массива хранения меток. По договоренности
   нулевое значение метки символизирует пустую ячйку массива */
void label_init()
{
  register int t;

  for(t = 0; t < NUM_LAB; t++)
    label_table[t].name[0] = '\0';
}
