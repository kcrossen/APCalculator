#include <string.h>

#include "config.h"

#include "StringExt.h"

char*
str_trim(char* string_to_trim)
{
    if (string_to_trim[0] == '\0') return string_to_trim;
    
    for(;;) {
        /* Clean up string by stripping any trailing whitespace */
        int i = strlen(string_to_trim);
        if (string_to_trim[i-1] <= ' ')
            string_to_trim[i-1] = '\0';
        else
            break;
    }

    if ((string_to_trim[0] <= ' ') && (string_to_trim[0] > '\0')) {
        char* cp = string_to_trim;
        while ((*cp <= ' ') && (*cp > '\0')) cp++;
        if (*cp == '\0') {
            string_to_trim[0] = '\0';
        }
        else {
            strncpy(string_to_trim, cp, (strlen(cp) + 1));
        }
    }

    return string_to_trim;
}

char*
str_copy(char* string_to_copy)
{
    char* cp = (char*)malloc(strlen(string_to_copy) + 3);
    memset(cp, '\0', strlen(string_to_copy) + 3);
    strcpy(cp, string_to_copy);
    return cp;
}

char*
str_skipchar(char* string_to_skipchar, char skipchar)
{
    char* cp = string_to_skipchar;
    while ((*cp == skipchar) && (*cp > '\0')) cp++;
    return cp;
}

char*
str_skipspace(char* string_to_skipblank)
{
    char* cp = string_to_skipblank;
    while ((*cp <= ' ') && (*cp > '\0')) cp++;
    return cp;
}

char*
str_skiptab(char* string_to_skiptab)
{
    char* cp = string_to_skiptab;
    while ((*cp == '\t') && (*cp > '\0')) cp++;
    return cp;
}

int
str_counttab(char* string_to_counttab)
{
    char* cp = string_to_counttab;
    while ((*cp == '\t') && (*cp > '\0')) cp++;
    return strlen(string_to_counttab) - strlen(cp);
}

