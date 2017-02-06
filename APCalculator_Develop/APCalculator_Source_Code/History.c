#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "libAPCalc.h"
#include "History.h"

#define MAX_HISTORY_COUNT 1000

#include "Modes.h"

typedef struct {
    int mode;
    char* cp_timestamp;
    char* cp_evaluation;
    char* cp_value;
} struct_history;

struct_history history[MAX_HISTORY_COUNT];
int next_history = 0;
int history_count = 0;

char*
str_replace_shorter(char* source_string, char* find_string, char* replacement_string) {
    if (source_string == NULL) return source_string;
    if (strlen(source_string) == 0) return source_string;
    // The replacement_string must be at least one character shorter...
    // ...that the find_string to leave room for the replacement_string...
    // ...terminating '\0' during interior replacements
    if (strlen(replacement_string) < strlen(find_string)) {
        char *cp = strstr(source_string, find_string);
        while (cp != NULL) {
            cp[0] = '\0';
            cp = cp + strlen(find_string);
            if (strlen(replacement_string) > 0) {
                strcat(source_string, replacement_string);
            }
            strcat(source_string, cp);
            cp = strstr(source_string, find_string);
        }
    }
    else if (strlen(replacement_string) == strlen(find_string)) {
        char *cp = strstr(source_string, find_string);
        while (cp != NULL) {
            strncpy(cp, replacement_string, strlen(replacement_string));
            cp = strstr(source_string, find_string);
        }
    }

    return source_string;
}

static void
save_eval(int save_mode, char* cp_save_timestamp,
          char* cp_save_evaluation, char* cp_save_value)
{
    history[next_history].mode = save_mode;

    if (history[next_history].cp_timestamp != NULL)
        free(history[next_history].cp_timestamp);
    if (history[next_history].cp_evaluation != NULL)
        free(history[next_history].cp_evaluation);
    if (history[next_history].cp_value != NULL)
        free(history[next_history].cp_value);

    if ((cp_save_timestamp == NULL) || (strlen(cp_save_timestamp) <= 0)) {
        time_t now;
        time(&now);
        char* time_str = (char*)malloc(100);
        strftime(time_str, 100, "%Y-%m-%d %H:%M:%S", localtime(&now));
        history[next_history].cp_timestamp = time_str;
    }
    else {
        history[next_history].cp_timestamp = (char*)malloc(strlen(cp_save_timestamp) + 3);
        memset(history[next_history].cp_timestamp, 0, (strlen(cp_save_timestamp) + 3));
        strcpy(history[next_history].cp_timestamp, cp_save_timestamp);
    }

    str_replace_shorter(cp_save_evaluation, (char*)"\r", (char*)"");
    history[next_history].cp_evaluation = (char*)malloc(strlen(cp_save_evaluation) + 3);
    memset(history[next_history].cp_evaluation, 0, (strlen(cp_save_evaluation) + 3));
    strcpy(history[next_history].cp_evaluation, cp_save_evaluation);
    
    str_replace_shorter(cp_save_value, (char*)"\r", (char*)"");
    history[next_history].cp_value = (char*)malloc(strlen(cp_save_value) + 3);
    memset(history[next_history].cp_value, 0, (strlen(cp_save_value) + 3));
    strcpy(history[next_history].cp_value, cp_save_value);

    next_history = (next_history + 1) % MAX_HISTORY_COUNT;
    if (history_count < MAX_HISTORY_COUNT) history_count = history_count + 1;
}

void
save_history_algebraic(char* cp_save_evaluation, char* cp_save_value)
{ save_eval(Algebraic_Mode, NULL, cp_save_evaluation, cp_save_value); }

void
save_history_program(char* cp_save_evaluation, char* cp_save_value)
{ save_eval(Program_Mode, NULL, cp_save_evaluation, cp_save_value); }

void
save_history_rpn(char* cp_save_stack, char* cp_save_memory)
{ save_eval(RPN_Mode, NULL, cp_save_stack, cp_save_memory); }

int saved_history_count(void) {return history_count;}

int
history_index_zero(void) {
    if (history_count < MAX_HISTORY_COUNT) return 0;
    else return next_history;
}

int
recall_history_mode(int history_index)
{return history[(history_index_zero() + (history_index - 1)) % MAX_HISTORY_COUNT].mode;}

char*
recall_history_timestamp(int history_index)
{return history[(history_index_zero() + (history_index - 1)) % MAX_HISTORY_COUNT].cp_timestamp;}

char*
recall_history(int history_index)
{return history[(history_index_zero() + (history_index - 1)) % MAX_HISTORY_COUNT].cp_evaluation;}

char*
recall_history_value(int history_index)
{return history[(history_index_zero() + (history_index - 1)) % MAX_HISTORY_COUNT].cp_value;}

void
clear_history(void) {
    next_history = 0;
    history_count = 0;
}

#define hismrkBegin "/* Begin \0"
#define hismrkBeginClose " */\0"
#define hismrkRPN "RPN\0"
#define hismrkAlgebraic "Algebraic\0"
#define hismrkProgram "Program\0"
#define hismrkEval "/* Eval */\0"
#define hismrkValue "/* Value */\0"
#define hismrkNewLine "\n\0"
#define hismrkEnd "/* End */\0"

char*
export_history(void) {
    int his_count = 0;
    int his_idx;

    for (his_idx = 1; (his_idx <= saved_history_count()); his_idx++)
        his_count = 
          his_count + 
          strlen(hismrkBegin) + strlen(hismrkAlgebraic) + 1 +
          strlen(recall_history_timestamp(his_idx)) + strlen(hismrkBeginClose) +
          strlen(hismrkNewLine) +
          strlen(hismrkEval) + strlen(hismrkNewLine) +
          strlen(recall_history(his_idx)) + strlen(hismrkNewLine) +
          strlen(hismrkValue) + strlen(hismrkNewLine) +
          strlen(recall_history_value(his_idx)) + strlen(hismrkNewLine) +
          strlen(hismrkEnd) + strlen(hismrkNewLine) + strlen(hismrkNewLine);
    his_count = his_count + 3;
    char* cp_history = (char*)malloc(his_count);
    memset(cp_history, '\0', his_count);
    for (his_idx = 1; (his_idx <= saved_history_count()); his_idx++) {
        strcat(cp_history, hismrkBegin);
        if (recall_history_mode(his_idx) == RPN_Mode)
            strcat(cp_history, hismrkRPN);
        else if ((recall_history_mode(his_idx) == Algebraic_Mode) ||
                 (recall_history_mode(his_idx) == Algebraic_Interactive_Mode))
            strcat(cp_history, hismrkAlgebraic);
        else if (recall_history_mode(his_idx) == Program_Mode)
            strcat(cp_history, hismrkProgram);
        else
            strcat(cp_history, hismrkAlgebraic);
        strcat(cp_history, (char*) " ");
        strcat(cp_history, str_trim(recall_history_timestamp(his_idx)));
        strcat(cp_history, hismrkBeginClose);
        strcat(cp_history, hismrkNewLine);
        strcat(cp_history, hismrkEval);
        strcat(cp_history, hismrkNewLine);
        strcat(cp_history, str_trim(recall_history(his_idx)));
        strcat(cp_history, hismrkNewLine);
        strcat(cp_history, hismrkValue);
        strcat(cp_history, hismrkNewLine);
        strcat(cp_history, str_trim(recall_history_value(his_idx)));
        strcat(cp_history, hismrkNewLine);
        strcat(cp_history, hismrkEnd);
        strcat(cp_history, hismrkNewLine);
        strcat(cp_history, hismrkNewLine);
    }

    return cp_history;
}

void
import_history(char* cp_history) {
    char* cp_this = cp_history;
    char* cp_next;
    int hist_mode = RPN_Mode;
    
    clear_history();
    
    while (cp_this != NULL) {
        cp_this = strstr(cp_this, hismrkBegin);
        if (cp_this == NULL) break;
        cp_this = cp_this + strlen(hismrkBegin);

        cp_next = strstr(cp_this, hismrkBegin);

        char* cp_mode = cp_this; /* Start of mode */

        char* cp_datetime = strstr(cp_mode, (char*) " "); /* Start of timestamp */

        cp_this = strstr(cp_datetime, hismrkBeginClose);
        *cp_datetime = '\0'; /* Terminates mode */

        char* cp_eval = strstr(cp_this, hismrkEval);
        *cp_this = '\0'; /* Terminates timestamp */

        cp_eval = cp_eval + strlen(hismrkEval); /* Start of eval */

        char* cp_value = strstr(cp_eval, hismrkValue);
        *cp_value = '\0'; /* Terminates eval */
        cp_value = cp_value + strlen(hismrkValue); /* Start of value */

        cp_this = strstr(cp_value, hismrkEnd);
        *cp_this = '\0'; /* Terminates value */

        cp_datetime = str_trim(cp_datetime);

        cp_mode = str_trim(cp_mode);
        if (strcmp(cp_mode, hismrkRPN) == 0)
            hist_mode = RPN_Mode;
        else if (strcmp(cp_mode, hismrkAlgebraic) == 0)
            hist_mode = Algebraic_Mode;
        else if (strcmp(cp_mode, hismrkProgram) == 0)
            hist_mode = Program_Mode;

        cp_eval = str_trim(cp_eval);
        cp_value = str_trim(cp_value);
        save_eval(hist_mode, cp_datetime, cp_eval, cp_value);

        cp_this = cp_next;
    }
}
