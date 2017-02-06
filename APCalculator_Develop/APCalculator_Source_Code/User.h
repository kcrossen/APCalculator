#define size_t int

typedef enum {
    std_in = 1,
    std_out = 2,
    std_err = 4
} enum_text_stream;
   
typedef struct {
    enum_text_stream stream;
    char* cp_line;
} struct_stream_line;

void user_init(void);

void user_clear(void);

int user_mark(void);

void out_io_clear(void);
void out_io_flush(void);
char* out_io_get(void);

void out_chr(int ch);
void out_str(char *str);
void out_fmt(char *fmt, ...);

void err_io_clear(void);
void err_io_flush(void);
char* err_io_get(void);

void err_chr(int ch);
void err_str(char *str);
void err_fmt(char *fmt, ...);

void user_line(int stream, char* str);
int user_count(int stream, int return_mark);
char* user_return(int stream, int return_mark, char* line_init, char* line_tabreplace, char* line_term);
char* user_return_line(int stream, int return_mark, int line_index);

void user_flush(void);

void user_term(void);

int openstring(char *str, size_t num);
void closeinput(void);

