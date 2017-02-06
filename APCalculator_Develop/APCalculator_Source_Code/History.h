#define recall_stack_memory recall_history_value

char* str_replace_shorter(char* source_string, char* find_string, char* replacement_string);

void save_history_rpn(char* cp_save_stack, char* cp_save_memory);
void save_history_algebraic(char* cp_save_evaluation, char* cp_save_value);
void save_history_program(char* cp_save_evaluation, char* cp_save_value);

int saved_history_count(void);

int recall_history_mode(int history_index);
char* recall_history_timestamp(int history_index);
char* recall_history(int history_index);
char* recall_history_value(int history_index);

void clear_history(void);

char* export_history(void);
void import_history(char* cp_history);


