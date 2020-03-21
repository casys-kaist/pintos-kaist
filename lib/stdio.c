#include <stdio.h>
#include <ctype.h>
#include <inttypes.h>
#include <round.h>
#include <stdint.h>
#include <string.h>

/* Auxiliary data for vsnprintf_helper(). */
struct vsnprintf_aux {
	char *p;            /* Current output position. */
	int length;         /* Length of output string. */
	int max_length;     /* Max length of output string. */
};

static void vsnprintf_helper (char, void *);

/* Like vprintf(), except that output is stored into BUFFER,
   which must have space for BUF_SIZE characters.  Writes at most
   BUF_SIZE - 1 characters to BUFFER, followed by a null
   terminator.  BUFFER will always be null-terminated unless
   BUF_SIZE is zero.  Returns the number of characters that would
   have been written to BUFFER, not including a null terminator,
   had there been enough room. */
int
vsnprintf (char *buffer, size_t buf_size, const char *format, va_list args) {
	/* Set up aux data for vsnprintf_helper(). */
	struct vsnprintf_aux aux;
	aux.p = buffer;
	aux.length = 0;
	aux.max_length = buf_size > 0 ? buf_size - 1 : 0;

	/* Do most of the work. */
	__vprintf (format, args, vsnprintf_helper, &aux);

	/* Add null terminator. */
	if (buf_size > 0)
		*aux.p = '\0';

	return aux.length;
}

/* Helper function for vsnprintf(). */
static void
vsnprintf_helper (char ch, void *aux_) {
	struct vsnprintf_aux *aux = aux_;

	if (aux->length++ < aux->max_length)
		*aux->p++ = ch;
}

/* Like printf(), except that output is stored into BUFFER,
   which must have space for BUF_SIZE characters.  Writes at most
   BUF_SIZE - 1 characters to BUFFER, followed by a null
   terminator.  BUFFER will always be null-terminated unless
   BUF_SIZE is zero.  Returns the number of characters that would
   have been written to BUFFER, not including a null terminator,
   had there been enough room. */
int
snprintf (char *buffer, size_t buf_size, const char *format, ...) {
	va_list args;
	int retval;

	va_start (args, format);
	retval = vsnprintf (buffer, buf_size, format, args);
	va_end (args);

	return retval;
}

/* Writes formatted output to the console.
   In the kernel, the console is both the video display and first
   serial port.
   In userspace, the console is file descriptor 1. */
int
printf (const char *format, ...) {
	va_list args;
	int retval;

	va_start (args, format);
	retval = vprintf (format, args);
	va_end (args);

	return retval;
}

/* printf() formatting internals. */

/* A printf() conversion. */
struct printf_conversion {
	/* Flags. */
	enum {
		MINUS = 1 << 0,         /* '-' */
		PLUS = 1 << 1,          /* '+' */
		SPACE = 1 << 2,         /* ' ' */
		POUND = 1 << 3,         /* '#' */
		ZERO = 1 << 4,          /* '0' */
		GROUP = 1 << 5          /* '\'' */
	} flags;

	/* Minimum field width. */
	int width;

	/* Numeric precision.
	   -1 indicates no precision was specified. */
	int precision;

	/* Type of argument to format. */
	enum {
		CHAR = 1,               /* hh */
		SHORT = 2,              /* h */
		INT = 3,                /* (none) */
		INTMAX = 4,             /* j */
		LONG = 5,               /* l */
		LONGLONG = 6,           /* ll */
		PTRDIFFT = 7,           /* t */
		SIZET = 8               /* z */
	} type;
};

struct integer_base {
	int base;                   /* Base. */
	const char *digits;         /* Collection of digits. */
	int x;                      /* `x' character to use, for base 16 only. */
	int group;                  /* Number of digits to group with ' flag. */
};

static const struct integer_base base_d = {10, "0123456789", 0, 3};
static const struct integer_base base_o = {8, "01234567", 0, 3};
static const struct integer_base base_x = {16, "0123456789abcdef", 'x', 4};
static const struct integer_base base_X = {16, "0123456789ABCDEF", 'X', 4};

static const char *parse_conversion (const char *format,
		struct printf_conversion *,
		va_list *);
static void format_integer (uintmax_t value, bool is_signed, bool negative,
		const struct integer_base *,
		const struct printf_conversion *,
		void (*output) (char, void *), void *aux);
static void output_dup (char ch, size_t cnt,
		void (*output) (char, void *), void *aux);
static void format_string (const char *string, int length,
		struct printf_conversion *,
		void (*output) (char, void *), void *aux);

void
__vprintf (const char *format, va_list args,
		void (*output) (char, void *), void *aux) {
	for (; *format != '\0'; format++) {
		struct printf_conversion c;

		/* Literally copy non-conversions to output. */
		if (*format != '%') {
			output (*format, aux);
			continue;
		}
		format++;

		/* %% => %. */
		if (*format == '%') {
			output ('%', aux);
			continue;
		}

		/* Parse conversion specifiers. */
		format = parse_conversion (format, &c, &args);

		/* Do conversion. */
		switch (*format) {
			case 'd':
			case 'i':
				{
					/* Signed integer conversions. */
					intmax_t value;

					switch (c.type) {
						case CHAR:
							value = (signed char) va_arg (args, int);
							break;
						case SHORT:
							value = (short) va_arg (args, int);
							break;
						case INT:
							value = va_arg (args, int);
							break;
						case INTMAX:
							value = va_arg (args, intmax_t);
							break;
						case LONG:
							value = va_arg (args, long);
							break;
						case LONGLONG:
							value = va_arg (args, long long);
							break;
						case PTRDIFFT:
							value = va_arg (args, ptrdiff_t);
							break;
						case SIZET:
							value = va_arg (args, size_t);
							if (value > SIZE_MAX / 2)
								value = value - SIZE_MAX - 1;
							break;
						default:
							NOT_REACHED ();
					}

					format_integer (value < 0 ? -value : value,
							true, value < 0, &base_d, &c, output, aux);
				}
				break;

			case 'o':
			case 'u':
			case 'x':
			case 'X':
				{
					/* Unsigned integer conversions. */
					uintmax_t value;
					const struct integer_base *b;

					switch (c.type) {
						case CHAR:
							value = (unsigned char) va_arg (args, unsigned);
							break;
						case SHORT:
							value = (unsigned short) va_arg (args, unsigned);
							break;
						case INT:
							value = va_arg (args, unsigned);
							break;
						case INTMAX:
							value = va_arg (args, uintmax_t);
							break;
						case LONG:
							value = va_arg (args, unsigned long);
							break;
						case LONGLONG:
							value = va_arg (args, unsigned long long);
							break;
						case PTRDIFFT:
							value = va_arg (args, ptrdiff_t);
#if UINTMAX_MAX != PTRDIFF_MAX
							value &= ((uintmax_t) PTRDIFF_MAX << 1) | 1;
#endif
							break;
						case SIZET:
							value = va_arg (args, size_t);
							break;
						default:
							NOT_REACHED ();
					}

					switch (*format) {
						case 'o': b = &base_o; break;
						case 'u': b = &base_d; break;
						case 'x': b = &base_x; break;
						case 'X': b = &base_X; break;
						default: NOT_REACHED ();
					}

					format_integer (value, false, false, b, &c, output, aux);
				}
				break;

			case 'c':
				{
					/* Treat character as single-character string. */
					char ch = va_arg (args, int);
					format_string (&ch, 1, &c, output, aux);
				}
				break;

			case 's':
				{
					/* String conversion. */
					const char *s = va_arg (args, char *);
					if (s == NULL)
						s = "(null)";

					/* Limit string length according to precision.
Note: if c.precision == -1 then strnlen() will get
SIZE_MAX for MAXLEN, which is just what we want. */
					format_string (s, strnlen (s, c.precision), &c, output, aux);
				}
				break;

			case 'p':
				{
					/* Pointer conversion.
					   Format pointers as %#x. */
					void *p = va_arg (args, void *);

					c.flags = POUND;
					format_integer ((uintptr_t) p, false, false,
							&base_x, &c, output, aux);
				}
				break;

			case 'f':
			case 'e':
			case 'E':
			case 'g':
			case 'G':
			case 'n':
				/* We don't support floating-point arithmetic,
				   and %n can be part of a security hole. */
				__printf ("<<no %%%c in kernel>>", output, aux, *format);
				break;

			default:
				__printf ("<<no %%%c conversion>>", output, aux, *format);
				break;
		}
	}
}

/* Parses conversion option characters starting at FORMAT and
   initializes C appropriately.  Returns the character in FORMAT
   that indicates the conversion (e.g. the `d' in `%d').  Uses
 *ARGS for `*' field widths and precisions. */
static const char *
parse_conversion (const char *format, struct printf_conversion *c,
		va_list *args) {
	/* Parse flag characters. */
	c->flags = 0;
	for (;;) {
		switch (*format++) {
			case '-':
				c->flags |= MINUS;
				break;
			case '+':
				c->flags |= PLUS;
				break;
			case ' ':
				c->flags |= SPACE;
				break;
			case '#':
				c->flags |= POUND;
				break;
			case '0':
				c->flags |= ZERO;
				break;
			case '\'':
				c->flags |= GROUP;
				break;
			default:
				format--;
				goto not_a_flag;
		}
	}
not_a_flag:
	if (c->flags & MINUS)
		c->flags &= ~ZERO;
	if (c->flags & PLUS)
		c->flags &= ~SPACE;

	/* Parse field width. */
	c->width = 0;
	if (*format == '*') {
		format++;
		c->width = va_arg (*args, int);
	} else {
		for (; isdigit (*format); format++)
			c->width = c->width * 10 + *format - '0';
	}
	if (c->width < 0) {
		c->width = -c->width;
		c->flags |= MINUS;
	}

	/* Parse precision. */
	c->precision = -1;
	if (*format == '.') {
		format++;
		if (*format == '*') {
			format++;
			c->precision = va_arg (*args, int);
		} else {
			c->precision = 0;
			for (; isdigit (*format); format++)
				c->precision = c->precision * 10 + *format - '0';
		}
		if (c->precision < 0)
			c->precision = -1;
	}
	if (c->precision >= 0)
		c->flags &= ~ZERO;

	/* Parse type. */
	c->type = INT;
	switch (*format++) {
		case 'h':
			if (*format == 'h') {
				format++;
				c->type = CHAR;
			}
			else
				c->type = SHORT;
			break;

		case 'j':
			c->type = INTMAX;
			break;

		case 'l':
			if (*format == 'l') {
				format++;
				c->type = LONGLONG;
			}
			else
				c->type = LONG;
			break;

		case 't':
			c->type = PTRDIFFT;
			break;

		case 'z':
			c->type = SIZET;
			break;

		default:
			format--;
			break;
	}

	return format;
}

/* Performs an integer conversion, writing output to OUTPUT with
   auxiliary data AUX.  The integer converted has absolute value
   VALUE.  If IS_SIGNED is true, does a signed conversion with
   NEGATIVE indicating a negative value; otherwise does an
   unsigned conversion and ignores NEGATIVE.  The output is done
   according to the provided base B.  Details of the conversion
   are in C. */
static void
format_integer (uintmax_t value, bool is_signed, bool negative,
		const struct integer_base *b,
		const struct printf_conversion *c,
		void (*output) (char, void *), void *aux) {
	char buf[64], *cp;            /* Buffer and current position. */
	int x;                        /* `x' character to use or 0 if none. */
	int sign;                     /* Sign character or 0 if none. */
	int precision;                /* Rendered precision. */
	int pad_cnt;                  /* # of pad characters to fill field width. */
	int digit_cnt;                /* # of digits output so far. */

	/* Determine sign character, if any.
	   An unsigned conversion will never have a sign character,
	   even if one of the flags requests one. */
	sign = 0;
	if (is_signed) {
		if (c->flags & PLUS)
			sign = negative ? '-' : '+';
		else if (c->flags & SPACE)
			sign = negative ? '-' : ' ';
		else if (negative)
			sign = '-';
	}

	/* Determine whether to include `0x' or `0X'.
	   It will only be included with a hexadecimal conversion of a
	   nonzero value with the # flag. */
	x = (c->flags & POUND) && value ? b->x : 0;

	/* Accumulate digits into buffer.
	   This algorithm produces digits in reverse order, so later we
	   will output the buffer's content in reverse. */
	cp = buf;
	digit_cnt = 0;
	while (value > 0) {
		if ((c->flags & GROUP) && digit_cnt > 0 && digit_cnt % b->group == 0)
			*cp++ = ',';
		*cp++ = b->digits[value % b->base];
		value /= b->base;
		digit_cnt++;
	}

	/* Append enough zeros to match precision.
	   If requested precision is 0, then a value of zero is
	   rendered as a null string, otherwise as "0".
	   If the # flag is used with base 8, the result must always
	   begin with a zero. */
	precision = c->precision < 0 ? 1 : c->precision;
	while (cp - buf < precision && cp < buf + sizeof buf - 1)
		*cp++ = '0';
	if ((c->flags & POUND) && b->base == 8 && (cp == buf || cp[-1] != '0'))
		*cp++ = '0';

	/* Calculate number of pad characters to fill field width. */
	pad_cnt = c->width - (cp - buf) - (x ? 2 : 0) - (sign != 0);
	if (pad_cnt < 0)
		pad_cnt = 0;

	/* Do output. */
	if ((c->flags & (MINUS | ZERO)) == 0)
		output_dup (' ', pad_cnt, output, aux);
	if (sign)
		output (sign, aux);
	if (x) {
		output ('0', aux);
		output (x, aux);
	}
	if (c->flags & ZERO)
		output_dup ('0', pad_cnt, output, aux);
	while (cp > buf)
		output (*--cp, aux);
	if (c->flags & MINUS)
		output_dup (' ', pad_cnt, output, aux);
}

/* Writes CH to OUTPUT with auxiliary data AUX, CNT times. */
static void
output_dup (char ch, size_t cnt, void (*output) (char, void *), void *aux) {
	while (cnt-- > 0)
		output (ch, aux);
}

/* Formats the LENGTH characters starting at STRING according to
   the conversion specified in C.  Writes output to OUTPUT with
   auxiliary data AUX. */
static void
format_string (const char *string, int length,
		struct printf_conversion *c,
		void (*output) (char, void *), void *aux) {
	int i;
	if (c->width > length && (c->flags & MINUS) == 0)
		output_dup (' ', c->width - length, output, aux);
	for (i = 0; i < length; i++)
		output (string[i], aux);
	if (c->width > length && (c->flags & MINUS) != 0)
		output_dup (' ', c->width - length, output, aux);
}

/* Wrapper for __vprintf() that converts varargs into a
   va_list. */
void
__printf (const char *format,
		void (*output) (char, void *), void *aux, ...) {
	va_list args;

	va_start (args, aux);
	__vprintf (format, args, output, aux);
	va_end (args);
}

/* Dumps the SIZE bytes in BUF to the console as hex bytes
   arranged 16 per line.  Numeric offsets are also included,
   starting at OFS for the first byte in BUF.  If ASCII is true
   then the corresponding ASCII characters are also rendered
   alongside. */
void
hex_dump (uintptr_t ofs, const void *buf_, size_t size, bool ascii) {
	const uint8_t *buf = buf_;
	const size_t per_line = 16; /* Maximum bytes per line. */

	while (size > 0) {
		size_t start, end, n;
		size_t i;

		/* Number of bytes on this line. */
		start = ofs % per_line;
		end = per_line;
		if (end - start > size)
			end = start + size;
		n = end - start;

		/* Print line. */
		printf ("%016llx  ", (uintmax_t) ROUND_DOWN (ofs, per_line));
		for (i = 0; i < start; i++)
			printf ("   ");
		for (; i < end; i++)
			printf ("%02hhx%c",
					buf[i - start], i == per_line / 2 - 1? '-' : ' ');
		if (ascii) {
			for (; i < per_line; i++)
				printf ("   ");
			printf ("|");
			for (i = 0; i < start; i++)
				printf (" ");
			for (; i < end; i++)
				printf ("%c",
						isprint (buf[i - start]) ? buf[i - start] : '.');
			for (; i < per_line; i++)
				printf (" ");
			printf ("|");
		}
		printf ("\n");

		ofs += n;
		buf += n;
		size -= n;
	}
}
