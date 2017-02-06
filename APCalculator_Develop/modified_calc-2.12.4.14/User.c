#include <stdio.h>

#include "calc.h"

#include "args.h"
#include "decl.h"
#include "user.h"
#include "StringExt.h"

#define STREAM_LINES 1000

struct_stream_line stream_line[STREAM_LINES];
int stream_line_initialized = 0;
int current_stream_line = 0;

#define OUTBUFSIZE	1024		/* realloc size for output buffers */

STATIC char	*outbuf = NULL;		/* current diverted buffer */
STATIC size_t	outbufsize = 0;
STATIC size_t	outbufused = 0;

#define ERRBUFSIZE	200		/* realloc size for output buffers */

STATIC char	*errbuf = NULL;		/* current error buffer */
STATIC size_t	errbufsize;
STATIC size_t	errbufused;

void
user_init(void)
{
    int i;
	if (stream_line_initialized == 0)
	{  
       	for (i=0; i < STREAM_LINES; ++i) {
            stream_line[i].stream = 0;
            stream_line[i].cp_line = NULL;
		}
	}
	else
	{
       	for (i=0; i < STREAM_LINES; ++i) {
            stream_line[i].stream = 0;
            if (stream_line[i].cp_line != NULL)
            {
                free(stream_line[i].cp_line);
                stream_line[i].cp_line = NULL;
            }
		}
	}
	current_stream_line = 0;
	stream_line_initialized = 1;

	outbufused = 0;
	outbufsize = 0;
	outbuf = (char *) malloc(OUTBUFSIZE + 1);
	if (outbuf == NULL) {
		math_error("Cannot allocate std_out buffer");
		/*NOTREACHED*/
	}
	outbufsize = OUTBUFSIZE;
	
	errbufused = 0;
	errbufsize = 0;
	errbuf = (char *) malloc(ERRBUFSIZE + 1);
	if (errbuf == NULL) {
		math_error("Cannot allocate std_err buffer");
		/*NOTREACHED*/
	}
	errbufsize = ERRBUFSIZE;
}

int
user_mark(void) {
    return current_stream_line;
}

void
user_clear(void)
{
    out_io_clear();
    err_io_clear();
}

void
user_line(int stream, char* str)
{
    stream_line[current_stream_line].stream = stream;
    if (stream_line[current_stream_line].cp_line != NULL)
        free(stream_line[current_stream_line].cp_line);
    
    stream_line[current_stream_line].cp_line = (char*)malloc(strlen(str) + 3);
    memset(stream_line[current_stream_line].cp_line, 0, (strlen(str) + 3));

	if (stream_line[current_stream_line].cp_line == NULL) {
		/* math_error("Cannot realloc output string"); */
		/*NOTREACHED*/
	}
	else
	{
        strcpy(stream_line[current_stream_line].cp_line, str);
        current_stream_line = (current_stream_line + 1) % STREAM_LINES;
    }
}

int
user_count(int stream, int return_mark)
{
    int ec = 0;
    int i;
    
    for (i = return_mark; i != current_stream_line; i = (i + 1) % STREAM_LINES) {
        if (((stream_line[i].stream & stream) != 0) && (stream_line[i].cp_line != NULL)) ec++;
    }

    return ec;
}

char *
user_return(int stream, int return_mark, char* line_init, char* line_tabreplace, char* line_term)
{
    int ch_count = 0;
    int i, t;
    
    for (i = return_mark; i != current_stream_line; i = (i + 1) % STREAM_LINES) {
        if (((stream_line[i].stream & stream) != 0) && (stream_line[i].cp_line != NULL)) 
            ch_count = 
              ch_count + 
              strlen(line_init) + 
              (str_counttab(stream_line[i].cp_line) * strlen(line_tabreplace)) +
              strlen(str_skiptab(stream_line[i].cp_line)) + 
              strlen(line_term);
    }

	char* cp = (char*)malloc(ch_count + 3);
    memset(cp, 0, (ch_count + 3));

    for (i = return_mark; i != current_stream_line; i = (i + 1) % STREAM_LINES) {
        if (((stream_line[i].stream & stream) != 0) && (stream_line[i].cp_line != NULL)) {
            strcat(cp, line_init); 
            for (t = 1; (t <= str_counttab(stream_line[i].cp_line)); t++)
                strcat(cp, line_tabreplace);
            strcat(cp, str_skiptab(stream_line[i].cp_line)); 
            strcat(cp, line_term);
        }
    }
	
	return cp;
}

char *
user_return_line(int stream, int return_mark, int line_offset)
{
    int ch_count = 0;
    int i = (return_mark + line_offset) % STREAM_LINES;

    if (((stream_line[i].stream & stream) != 0) && (stream_line[i].cp_line != NULL)) 
        ch_count = ch_count + strlen(stream_line[i].cp_line);

	char* cp = (char*)malloc(ch_count + 3);
    memset(cp, 0, (ch_count + 3));

    if (((stream_line[i].stream & stream) != 0) && (stream_line[i].cp_line != NULL)) 
        strcat(cp, stream_line[i].cp_line);
	
	return cp;
}

void
user_flush(void)
{
    out_io_flush();
    err_io_flush();
}

void
user_term(void)
{
    int i;
	if (stream_line_initialized != 0)
	{  
       	for (i=0; i < STREAM_LINES; ++i) {
            if (stream_line[i].cp_line != NULL)
            {
                free(stream_line[i].cp_line);
                stream_line[i].cp_line = NULL;
            }
		}
	}

    if (outbuf != NULL) free(outbuf);
    outbuf = NULL;

	outbufused = 0;
	outbufsize = 0;
	
    if (errbuf != NULL) free(errbuf);
    errbuf = NULL;

	errbufused = 0;
	errbufsize = 0;
}

BOOL out_io_capture = FALSE;

void
out_io_clear(void)
{
    memset(outbuf, 0, outbufsize);
	outbufused = 0;
}

void
out_io_flush(void)
{
    if (outbufused > 0) {
        user_line(std_out, outbuf);
        out_io_clear();
	}
}

char *
out_io_get(void)
{
    char* cp = (char*)malloc(strlen(outbuf) + 3);
    memset(cp, 0, (strlen(outbuf) + 3));
    strcpy(cp, outbuf);
	return cp;
}

void
out_chr(int ch)
{
	char	*cp;

	if (!out_io_capture && (ch == '\n')) {
        out_io_flush();
    }
	else {
        if (outbufused >= outbufsize) {
    		cp = (char *)realloc(outbuf, outbufsize + OUTBUFSIZE + 1);
    		if (cp == NULL) {
    			math_error("Cannot realloc output string");
    			/*NOTREACHED*/
    		}
    		outbuf = cp;
    		outbufsize += OUTBUFSIZE;
        }
	    outbuf[outbufused++] = (char)ch;
	}
}

void
out_str(char *str)
{
	int i;

	for (i = 0; i < strlen(str); i++) out_chr(str[i]);
}

void
out_fmt(char *fmt, ...)
{
	va_list ap;
	char buf[BUFSIZ+1];

	va_start(ap, fmt);
	vsnprintf(buf, BUFSIZ, fmt, ap);
	va_end(ap);
	buf[BUFSIZ] = '\0';
	out_str(buf);
}

void
err_io_clear(void)
{
    memset(errbuf, 0, errbufsize);
	errbufused = 0;
}

void
err_io_flush(void)
{
    if (errbufused > 0) {
        user_line(std_err, errbuf);
        err_io_clear();
	}
}

char *
err_io_get(void)
{
	return errbuf;
}

void
err_chr(int ch)
{
	char	*cp;

	if (ch == '\n') {
        err_io_flush();
    }
	else {
        if (errbufused >= errbufsize) {
    		cp = (char *)realloc(errbuf, errbufsize + ERRBUFSIZE + 1);
    		if (cp == NULL) {
    			math_error("Cannot realloc std_err buffer");
    			/*NOTREACHED*/
    		}
    		errbuf = cp;
    		errbufsize += ERRBUFSIZE;
        }
	    errbuf[errbufused++] = (char)ch;
	}
}

void
err_str(char *str)
{
	int i;

	for (i = 0; i < strlen(str); i++) err_chr(str[i]);
}

void
err_fmt(char *fmt, ...)
{
	va_list ap;
	char buf[BUFSIZ+1];

	va_start(ap, fmt);
	vsnprintf(buf, BUFSIZ, fmt, ap);
	va_end(ap);
	buf[BUFSIZ] = '\0';
	err_str(buf);
}

#define TTYSIZE		100	/* reallocation size for terminal buffers */
#define IS_READ		1	/* reading normally */
#define IS_REREAD	2	/* reread current character */
#define chartoint(ch)	((ch) & 0xff)	/* make sure char is not negative */

int i_state;		/* state (read, reread) */
int i_char;		/* currently read char */
long i_line;		/* line number */
char *i_cp;		/* pointer to string character to be read */
char *i_str;		/* start of string copy to be read, or NULL */
long i_num;		/* number of string characters remaining */

STATIC int linesize;		/* current max size of input line */
STATIC char *linebuf;		/* current input line buffer */
STATIC char *prompt;		/* current prompt for terminal */
STATIC BOOL noprompt;		/* TRUE if should not print prompt */

/*
 * Open a string for scanning, num characters to be read.
 * String is copied into local memory so it can be trashed afterwards.
 * Returns -1 if cannot open string.
 *
 * given:
 *	str		string to be opened
 *	num		lengh of string to open
 */
int
openstring(char *str, size_t num)
{
	char *cp;		/* copied string */

	cp = (char *) malloc(num + 1);
	if (cp == NULL)
		 return -1;
	strncpy(cp, str, num);
	cp[num] = '\0';	/* firewall */
	i_state = IS_READ;
	i_char = '\0';
	i_cp = cp;
	i_str = cp;
	i_num = num;
	i_line = 1;
	return 0;
}

/*
 * Read the next character from the current input source.
 * End of file closes current input source, and returns EOF character.
 */
int
nextchar(void)
{
	int ch = EOF;			/* current input character */

	if (i_state == IS_REREAD) {	/* rereading current char */
		 ch = i_char;
		 i_state = IS_READ;
		 if (ch == '\n')
			i_line++;
		 return ch;
	}
	if (i_str) {		/* from string */
		if (i_num) {
			ch = chartoint(*i_cp++); /* ch = chartoint(*cip->i_cp++); */
			i_num--;
		} else {
			ch = EOF;
		}
	}
	i_char = ch;	/* save for rereads */
	if (ch == '\n')
		i_line++;
	return ch;
}

/*
 * Read in the next line of input from the current input source.
 * The line is terminated with a null character, and does not contain
 * the final newline character.	 The returned string is only valid
 * until the next such call, and so must be copied if necessary.
 * Returns NULL on end of file.
 */
char *
nextline(void)
{
	char *cp;
	int ch;
	int len;

	cp = linebuf;
	if (linesize == 0) {
		cp = (char *)malloc(TTYSIZE + 1);
		if (cp == NULL) {
			math_error("Cannot allocate line buffer");
			/*NOTREACHED*/
		}
		linebuf = cp;
		linesize = TTYSIZE;
	}
	len = 0;
	for (;;) {
		noprompt = TRUE;
		ch = nextchar();
		noprompt = FALSE;
		if (ch == EOF)
			return NULL;
		if (ch == '\0')
			continue;
		if (ch == '\n')
			break;
		if (len >= linesize) {
			cp = (char *)realloc(cp, linesize + TTYSIZE + 1);
			if (cp == NULL) {
				math_error("Cannot realloc line buffer");
				/*NOTREACHED*/
			}
			linebuf = cp;
			linesize += TTYSIZE;
		}
		cp[len++] = (char)ch;
	}
	cp[len] = '\0';
	return linebuf;
}

/*
 * Return the current line number.
 */
long
linenumber(void)
{
    return i_line;
}

/*
 * Restore the next character to be read again on the next nextchar call.
 */
void
reread(void)
{
	if (i_state == IS_REREAD)
		return;
	i_state = IS_REREAD;
	if (i_char == '\n')
		i_line--;
}

/*
 * Set the prompt for terminal input.
 */
void
setprompt(char *str)
{
	prompt = str;
	noprompt = TRUE /*FALSE*/;
}

/*
 * Close the current input source.
 */
void
closeinput(void)
{
	if (i_str) free(i_str);
}

/*
 * Reset the input sources back to the initial state.
 */
void
resetinput(void)
{
	closeinput();
	noprompt = TRUE /*FALSE*/;
}

BOOL
inputisterminal(void)
{
	return FALSE;
}
