typedef enum {
    std_in = 1,
    std_out = 2,
    std_err = 4
} enum_text_stream;
   
typedef struct {
    enum_text_stream stream;
    char* cp_line;
} struct_stream_line;

E_FUNC void user_init(void);

E_FUNC void user_clear(void);

E_FUNC int user_mark(void);

E_FUNC void out_io_clear(void);
E_FUNC void out_io_flush(void);
E_FUNC char* out_io_get(void);

E_FUNC void out_chr(int ch);
E_FUNC void out_str(char *str);
E_FUNC void out_fmt(char *fmt, ...);

E_FUNC void err_io_clear(void);
E_FUNC void err_io_flush(void);
E_FUNC char* err_io_get(void);

E_FUNC void err_chr(int ch);
E_FUNC void err_str(char *str);
E_FUNC void err_fmt(char *fmt, ...);

E_FUNC void user_line(int stream, char* str);
E_FUNC int user_count(int stream, int return_mark);
E_FUNC char* user_return(int stream, int return_mark, char* line_init, char* line_tabreplace, char* line_term);
E_FUNC char* user_return_line(int stream, int return_mark, int line_index);

E_FUNC void user_flush(void);

E_FUNC void user_term(void);

E_FUNC int openstring(char *str, size_t num);
E_FUNC void closeinput(void);
