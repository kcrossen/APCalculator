#include <stdio.h>

#include "calc.h"

#include "args.h"
#include "decl.h"
#include "user.h"
#include "UserUtil.h"

EXTERN BOOL out_io_capture;
/*
 * external STDIO functions
 */
E_FUNC void math_setfp(FILE *fp);

/*
 * Print a formatted string similar to printf.	Various formats of output
 * are possible, depending on the format string AND the actual types of the
 * values.  Mismatches do not cause errors, instead something reasonable is
 * printed instead.  The output goes to stdout.
 *
 * given:
 *	id		file id to print to
 *	count		print count
 *	fmt		standard format string
 *	vals		table of values to print
 */
char *
user_printf(char *fmt, int count, VALUE **vals)
{
	VALUE *vp;
	char *str;
	int ch;
	size_t len;
	int oldmode, newmode;
	long olddigits, newdigits;
	long width, precision;
	BOOL didneg, didprecision;
	BOOL printstring;
	BOOL printchar;

	out_io_flush();
	out_io_capture = TRUE;

	printstring = FALSE;
	printchar = FALSE;

	while ((ch = *fmt++) != '\0') {
		if (ch != '%') {
			math_chr(ch);
			continue;
		}

		/*
		 * Here to handle formats.
		 */
		didneg = FALSE;
		didprecision = FALSE;
		width = 0;
		precision = 0;

		ch = *fmt++;
		if (ch == '-') {
			didneg = TRUE;
			ch = *fmt++;
		}
		while ((ch >= '0') && (ch <= '9')) {
			width = width * 10 + (ch - '0');
			ch = *fmt++;
		}
		if (ch == '.') {
			didprecision = TRUE;
			ch = *fmt++;
			while ((ch >= '0') && (ch <= '9')) {
				precision = precision * 10 + (ch - '0');
				ch = *fmt++;
			}
		}
		if (ch == 'l')
			ch = *fmt++;

		oldmode = conf->outmode;
		newmode = oldmode;
		olddigits = conf->outdigits;
		newdigits = olddigits;
		if (didprecision)
			newdigits = precision;

		switch (ch) {
		case 's':
			printstring = TRUE;
		case 'c':
			printchar = TRUE;
		case 'd':
			break;
		case 'f':
			newmode = MODE_REAL;
			break;
		case 'e':
			newmode = MODE_EXP;
			break;
		case 'r':
			newmode = MODE_FRAC;
			break;
		case 'o':
			newmode = MODE_OCTAL;
			break;
		case 'x':
			newmode = MODE_HEX;
			break;
		case 'b':
			newmode = MODE_BINARY;
			break;
		case 0:
			math_setfp(stdout);
			return 0;
		default:
			math_chr(ch);
			continue;
		}

		if (--count < 0) {
			while (width-- > 0)
				math_chr(' ');
			continue;
		}
		vp = *vals++;

		math_setdigits(newdigits);
		math_setmode(newmode);

		/*
		 * If there is no width specification, or if the type of
		 * value requires multiple lines, then just output the
		 * value directly.
		 */
		if ((width == 0) ||
			(vp->v_type == V_MAT) || (vp->v_type == V_LIST)) {
			switch(vp->v_type) {
			case V_OCTET:
				if (printstring)
					math_str((char *)vp->v_octet);
				else if (printchar)
					math_chr(*vp->v_octet);
				else
					printvalue(vp, PRINT_NORMAL);
				break;
			case V_BLOCK:
				if (printstring)
					math_str((char *)
						 vp->v_block->data);
				else if (printchar)
					math_chr(*vp->v_block->data);
				else
					printvalue(vp, PRINT_NORMAL);
				break;
			case V_NBLOCK:
				if (printstring) {
					if (vp->v_nblock->blk->data !=
					    NULL)
						math_str((char *)
							 vp->v_nblock
							 ->blk->data);
				} else if (printchar) {
					if (vp->v_nblock->blk->data !=
					    NULL)
						math_chr(*vp->v_nblock->
							 blk->data);
				} else {
					printvalue(vp, PRINT_NORMAL);
				}
				break;
			default:
				printvalue(vp, PRINT_NORMAL);
			}

			math_setmode(oldmode);
			math_setdigits(olddigits);
			continue;
		}


		/*
		 * There is a field width.  Collect the output in a string,
		 * print it padded appropriately with spaces, and free it.
		 * However, if the output contains a newline, then ignore
		 * the field width.
		 */
		/* @krc@ math_divertio(); @krc@ */		
		switch(vp->v_type) {
		case V_OCTET:
			if (printstring)
				math_str((char *)vp->v_octet);
			else if (printchar)
				math_chr(*vp->v_octet);
			else
				printvalue(vp, PRINT_NORMAL);
			break;
		case V_BLOCK:
			if (printstring)
				math_str((char *)vp->v_block->data);
			else if (printchar)
				math_chr(*vp->v_block->data);
			else
				printvalue(vp, PRINT_NORMAL);
			break;
		case V_NBLOCK:
			if (printstring) {
				if (vp->v_nblock->blk->data != NULL)
					math_str((char *)
						 vp->v_nblock->blk->data);
			}
			else if (printchar) {
				if (vp->v_nblock->blk->data != NULL)
					math_chr(*vp->v_nblock->blk->data);
			}
			else
				printvalue(vp, PRINT_NORMAL);
			break;
		default:
			printvalue(vp, PRINT_NORMAL);
		}
		/* @krc@ str = math_getdivertedio(); @krc@ */
		str = out_io_get();
		out_io_clear();
		/* Now prepend some spaces */
		if (strchr(str, '\n'))
			width = 0;
		len = strlen(str);
		while (!didneg && ((size_t)width > len)) {
			width--;
			math_chr(' ');
		}
		math_str(str);
		free(str);
		while (didneg && ((size_t)width > len)) {
			width--;
			math_chr(' ');
		}
		math_setmode(oldmode);
		math_setdigits(olddigits);
	}
	math_setfp(stdout);
	
	str = out_io_get();
	out_io_clear();
	out_io_capture = FALSE;
	return str;
}

int
fscanfid(FILEID id, char *fmt, int count, VALUE **vals)
{
	return -2;
}


int
scanfstr(char *str, char *fmt, int count, VALUE **vals)
{
	return EOF;
}

#if 0
/*
 * getscanfield - scan a field separated by some characters
 *
 * given:
 *	fp		FILEID to scan
 *	skip
 *	width		max field width
 *	scannum		Number of characters in scanset
 *	scanptr		string of characters considered separators
 *	strptr		pointer to where the new field pointer may be found
 */
S_FUNC void
getscanfield(FILE *fp, BOOL skip, unsigned int width, int scannum, char *scanptr, char **strptr)
{
	char *str;		/* current string */
	unsigned long len;	/* current length of string */
	unsigned long totlen;	/* total length of string */
	char buf[READSIZE];	/* temporary buffer */
	int c;
	char *b;
	BOOL comp;		/* Use complement of scanset */
	unsigned int chnum;

	totlen = 0;
	str = NULL;

	comp = (scannum < 0);
	if (comp)
		scannum = -scannum;

	chnum = 0;

	for (;;) {
		len = 0;
		b = buf;
		for(;;) {
			c = fgetc(fp);
			if (c == EOF || c == '\0')
				break;
			chnum++;
			if(scannum &&
			   ((memchr(scanptr,c,scannum)==NULL) ^ comp))
				break;
			if (!skip) {
				*b++ = c;
				len++;
				if (len >= READSIZE)
					break;
			}
			if (chnum == width)
				break;
		}
		if (!skip) {
			if (totlen)
				str = (char *) realloc(str, totlen + len + 1);
			else
				str = (char *) malloc(len + 1);
			if (str == NULL) {
				math_error("Out of memory for scanning");
				/*NOTREACHED*/
			}
			if (len)
				memcpy(&str[totlen], buf, len);
			totlen += len;
		}
		if (len < READSIZE)
			break;
	}

	if (!(width && chnum == width) && c != '\0')
		ungetc(c, fp);

	if (!skip) {
		str[totlen] = '\0';
		*strptr = str;
	}
}

/*
 * getscanwhite - scan a field separated by whitespace
 *
 * given:
 *	fp		FILEID to scan
 *	skip
 *	width		max field width
 *	scannum		Number of characters in scanset
 *	strptr		pointer to where the new field pointer may be found
 */
S_FUNC void
getscanwhite(FILE *fp, BOOL skip, unsigned int width, int scannum, char **strptr)
{
	char *str;		/* current string */
	unsigned long len;	/* current length of string */
	unsigned long totlen;	/* total length of string */
	char buf[READSIZE];	/* temporary buffer */
	int c;
	char *b;
	BOOL comp;		/* Use complement of scanset */
	unsigned int chnum;

	totlen = 0;
	str = NULL;

	comp = (scannum < 0);
	if (comp)
		scannum = -scannum;

	chnum = 0;

	for (;;) {
		len = 0;
		b = buf;
		for(;;) {
			c = fgetc(fp);
			if (c == EOF || c == '\0')
				break;
			chnum++;
			if(scannum && (!isspace(c) ^ comp))
				break;
			if (!skip) {
				*b++ = c;
				len++;
				if (len >= READSIZE)
					break;
			}
			if (chnum == width)
				break;
		}
		if (!skip) {
			if (totlen)
				str = (char *) realloc(str, totlen + len + 1);
			else
				str = (char *) malloc(len + 1);
			if (str == NULL) {
				math_error("Out of memory for scanning");
				/*NOTREACHED*/
			}
			if (len)
				memcpy(&str[totlen], buf, len);
			totlen += len;
		}
		if (len < READSIZE)
			break;
	}

	if (!(width && chnum == width) && c != '\0')
		ungetc(c, fp);

	if (!skip) {
		str[totlen] = '\0';
		*strptr = str;
	}
}

S_FUNC int
fscanfile(FILE *fp, char *fmt, int count, VALUE **vals)
{
	int assnum;	/* Number of assignments made */
	int c;		/* Character read from file */
	char f;		/* Character read from format string */
	int scannum;	/* Number of characters in scanlist */
	char *scanptr;	/* Start of scanlist */
	char *str;
	BOOL comp;	/* True scanset is complementary */
	BOOL skip;	/* True if string to be skipped rather than read */
	int width;
	VALUE *var;	/* lvalue to be assigned to */
	unsigned short subtype;	/* for var->v_subtype */
	FILEPOS cur;	/* current location */

	if (feof(fp))
		return EOF;

	assnum = 0;

	for (;;) {
		for (;;) {
			f = *fmt++;
			if (isspace((int)f)) {
				getscanwhite(fp,1,0,6,NULL);
				do {
					f = *fmt++;
				} while (isspace((int)f));
			}
			c = fgetc(fp);
			if (c == EOF)
				return assnum;
			if (f == '%') {
				f = *fmt++;
				if (f != '%' && f != '\0')
					break;
			}
			if (f != c || f == '\0') {
				ungetc(c, fp);
				return assnum;
			}
		}
		ungetc(c, fp);
		skip = (f == '*');
		if (!skip && count == 0) {
			return assnum;
		}
		if (skip)
			f = *fmt++;
		width = 0;
		while (f >= '0' && f <= '9') {
			width = 10 * width + f - '0';
			f = *fmt++;
		}
		switch (f) {
		case 'c':
			if (width == 0)
				width = 1;
			getscanfield(fp,skip,width,0,NULL,&str);
			break;
		case 's':
			getscanwhite(fp,1,0,6,NULL);
			if (feof(fp))
				return assnum;
			getscanwhite(fp,skip,width,-6,&str);
			break;
		case '[':
			f = *fmt;
			comp = (f == '^');
			if (comp)
				f = *++fmt;
			scanptr = fmt;
			if (f == '\0')
				return assnum;
			fmt = strchr((f == ']' ? fmt + 1 : fmt), ']');
			if (fmt == NULL)
				return assnum;
			scannum = fmt - scanptr;
			if (comp)
				scannum = -scannum;
			fmt++;
			getscanfield(fp,skip,
				 width,scannum,scanptr,&str);
			break;
		case 'f':
		case 'e':
		case 'r':
		case 'i':
			getscanwhite(fp,1,0,6, NULL);
			if (feof(fp))
				return assnum;
			if (skip) {
				fskipnum(fp);
				continue;
			}
			assnum++;
			var = *vals++;
			if (var->v_type != V_ADDR)
			math_error("This should not happen!!");
			var = var->v_addr;
			subtype = var->v_subtype;
			freevalue(var);
			count--;
			freadsum(fp, var);
			var->v_subtype = subtype;
			continue;
		case 'n':
			assnum++;
			var = *vals++;
			count--;
			if (var->v_type != V_ADDR)
				math_error("This should not happen!!");
			var = var->v_addr;
			subtype = var->v_subtype;
			freevalue(var);
			var->v_type = V_NUM;
			var->v_num = qalloc();
			f_tell(fp, &cur);
			var->v_num->num = filepos2z(cur);
			var->v_subtype = subtype;
			continue;
		default:
			err_str("Unsupported scan specifier");
			return assnum;
		}
		if (!skip) {
			assnum++;
			var = *vals++;
			count--;
			if (var->v_type != V_ADDR)
				math_error("Assigning to nonvariable");
			var = var->v_addr;
			subtype = var->v_subtype;
			freevalue(var);
			var->v_type = V_STR;
			var->v_str = makestring(str);
		}
	}
}

int
fscanfid(FILEID id, char *fmt, int count, VALUE **vals)
{
	FILEIO *fiop;
	FILE *fp;
	FILEPOS fpos;

	fiop = findid(id, FALSE);
	if (fiop == NULL)
		return -2;

	fp = fiop->fp;

	if (fiop->action == 'w') {
		f_tell(fp, &fpos);
		fflush(fp);
		if (f_seek_set(fp, &fpos) < 0)
			return -4;
	}
	fiop->action = 'r';

	return fscanfile(fp, fmt, count, vals);
}


int
scanfstr(char *str, char *fmt, int count, VALUE **vals)
{
	FILE *fp;
	int i;

	fp = tmpfile();
	if (fp == NULL)
		return EOF;
	fputs(str, fp);
	rewind(fp);
	i = fscanfile(fp, fmt, count, vals);
	fclose(fp);
	return i;
}
#endif
