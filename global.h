/*
 *  $Id: global.h,v 1.1 1993/10/09 18:24:27 sev Exp sev $
 *
 * ---------------------------------------------------------- 
 *
 * $Log: global.h,v $
 * Revision 1.1  1993/10/09  18:24:27  sev
 * Initial revision
 *
 *
 */

#ifdef MAIN
#define EXTERN
#else
#define EXTERN extern
#endif

EXTERN jmp_buf e_buf; /* содержит среду для long_jmp() */
EXTERN char progname[40];
EXTERN char token[80];
EXTERN char token_type, tok;
EXTERN char *prog; /* содержит выражение для анализа */
EXTERN int ftos;	/* индекс начала стэка for */
EXTERN int gtos;	/* индекс хачала стэка gosub */
EXTERN int variables[26];	/* переменные пользователя */
