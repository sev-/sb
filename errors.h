/*
 *  $Id: errors.h,v 1.1 1993/10/09 18:24:27 sev Exp sev $
 *
 * ---------------------------------------------------------- 
 *
 * $Log: errors.h,v $
 * Revision 1.1  1993/10/09  18:24:27  sev
 * Initial revision
 *
 *
 */

#define E_SYNTAX	0	/* синтаксическая */
#define E_BRACKETS	1	/* Непарные скобки */
#define E_BADEXP	2	/* Это не выражение */
#define E_NEEDEQU	3	/* Необходим знак = */
#define E_NEEDVAR	4	/* Необходима переменная */
#define E_TOOLABELS	5	/* Слишком много меток */
#define E_DUPLABELS	6	/* Дублирование меток */
#define E_NOLABEL	7	/* нет такой метки */
#define E_NEEDTHEN	8	/* необходим then */
#define E_NEEDTO	9	/* необходим to */
#define E_TOOFOR	10	/* много вложено for */
#define E_BADNEXT	11	/* next без for */
#define E_TOOGOSUB	12	/* много вложено gosub */
#define E_BADRETURN	13	/* return без gosub */
#define E_BADSTEP	14	/* шаг равен 0 */
