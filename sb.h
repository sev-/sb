/*
 *  $Id: sb.h,v 1.1 1993/10/09 18:24:27 sev Exp sev $
 *
 * ---------------------------------------------------------- 
 *
 * $Log: sb.h,v $
 * Revision 1.1  1993/10/09  18:24:27  sev
 * Initial revision
 *
 *
 */
 
#include <stdio.h>
#include <setjmp.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>

#define NUM_LAB 	100
#define LAB_LEN		10
#define FOR_NEST	25
#define SUB_NEST	25
#define PROG_SIZE	10000

#include "proto.h"
#include "global.h"
#include "lex.h"
#include "errors.h"

