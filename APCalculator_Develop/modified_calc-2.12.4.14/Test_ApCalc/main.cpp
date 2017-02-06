#include <stdio.h>
#include <iostream>

#if !defined(TRUE)
#define TRUE	((BOOL) 1)			/* booleans */
#endif
#if !defined(FALSE)
#define FALSE	((BOOL) 0)
#endif

/* Extern "C" */
#ifdef __cplusplus
extern "C" {
#endif

#include "libAPCalc.h"

#ifdef __cplusplus
}
#endif
/* Extern "C" */

#include "APCalc_Init.h"

#define tst_str (char*) "base(10);base2(0);"

int main(void)
{
    int err;

    libcalc_call_me_first();

    user_init();

    reinitialize();

    int userMark = user_mark();

    (void) openstring(tst_str, strlen(tst_str));
    err = execute_commands(TRUE);
    closeinput();


    printf("Hello World!\n");
    /* std::cout << "Hello World!\n"; */
    return 0;
}

/* CALC_SRC=1;LONG_BITS=64;BYTE_ORDER=1234;__BYTE_ORDER=1234 */
