/*
 *  $Id: sb.c,v 1.1 1993/10/09 18:24:27 sev Exp sev $
 *
 * ---------------------------------------------------------- 
 *
 * $Log: sb.c,v $
 * Revision 1.1  1993/10/09  18:24:27  sev
 * Initial revision
 *
 *
 */
 
#define MAIN
#include "sb.h"

main(argc, argv)
int argc;
char **argv;
{
  char in[80];
  int answer;
  char *p_buf;
  char *t;

  if(argc != 2)
  {
    puts("SB version 1.1");
    printf("Используйте формат:\n\t%s filename\n", argv[0]);
    exit(1);
  }

  strncpy(progname, argv[0], 40);

  /* выделение памяти */
  if(!(p_buf = (char *)malloc(PROG_SIZE)))
  {
    printf("%s: Как ни странно, но Malloc error\n", argv[0]);
    exit(2);
  }

  /* Loading a program */
  if(!load_program(p_buf, argv[1]))
    exit(3);

  if(setjmp(e_buf))
    exit(4);

  prog = p_buf;
  scan_labels();
  ftos = 0;
  gtos = 0;

  do
  {
    token_type = get_token();	/* проверка на оператор присваиванийа */
    if(token_type == VARIABLE)
    {
      putback();
      assignment();
    }
    else	/* это команда */
      switch(tok)
      {
	case PRINT:
	  print();
	  break;
	case IF:
	  exec_if();
	  break;
	case GOTO:
	  exec_goto();
	  break;
	case FOR:
	  exec_for();
	  break;
	case NEXT:
	  next();
	  break;
	case INPUT:
	  input();
	  break;
	case GOSUB:
	  gosub();
	  break;
	case RETURN:
	  greturn();
	  break;
	case END:
	  exit(0);
	  break;
      }
  } while(tok != FINISHED);
}

load_program(p, fname)		/* Загрузка программы */
char *p;
char *fname;
{
  FILE *fp;
  int i = 0;

  if(!(fp = fopen(fname,"r")))
    return 0;

  i = 0;
  do
  {
    *p = fgetc(fp);
    p++;
    i++;
  }

  while(!feof(fp) && i < PROG_SIZE);
  *(p-2) = '\0';
  fclose(fp);

  return 1;
}
