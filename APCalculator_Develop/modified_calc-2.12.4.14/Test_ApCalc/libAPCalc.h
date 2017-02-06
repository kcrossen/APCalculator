#define BOOL int

#define MAXCMD 8000	/* maximum length of command invocation */
#define MAXOPERAND 255
#define MAXHISTORY 1000000

void libcalc_call_me_first(void);
void initialize(void);
void reinitialize(void);
/* @krc@ E_FUNC void getcommands(BOOL toplevel); @krc@ */
int execute_commands(BOOL toplevel);
void libcalc_call_me_last(void);

// char* str_trim(char* string_to_trim);

// char* str_copy(char* string_to_copy);

// char* str_skipchar(char* string_to_skipchar, char skipchar);

// char* str_skipspace(char* string_to_skipblank);

// char* str_skiptab(char* string_to_skiptab);

// int str_counttab(char* string_to_counttab);

#include "StringExt.h"

// static int userMark;

// static char last_operand[MAXOPERAND];

// static char cmdstr[MAXCMD+1+1+1];	/* command line expression + "\n\0" + guard */

#include "User.h"
