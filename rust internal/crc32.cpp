#include "encryption.hpp"
#include "memory.hpp"

#define ZEROPAD 1       /* pad with zero */
#define SIGN    2       /* unsigned/signed long */
#define PLUS    4       /* show plus */
#define SPACE   8       /* space if plus */
#define LEFT    16      /* left justified */
#define SPECIAL 32      /* 0x */
#define LARGE   64      /* use 'ABCDEF' instead of 'abcdef' */
#define REMOVEHEX   256     /* use 256 as remve 0x frim BASE 16  */
typedef struct {
    unsigned int mantissal : 32;
    unsigned int mantissah : 20;
    unsigned int exponent : 11;
    unsigned int sign : 1;
} ex_double_t;

typedef struct _UNICODE_STRING {
    USHORT Length;
    USHORT MaximumLength;
    PWSTR  Buffer;
} UNICODE_STRING;
typedef UNICODE_STRING* PUNICODE_STRING;

typedef struct _ANSI_STRING {
    USHORT Length;
    USHORT MaximumLength;
    PSTR   Buffer;
} ANSI_STRING;
typedef ANSI_STRING* PANSI_STRING;

static
__inline
int
_isinf(double __x)
{
    union
    {
        double* __x;
        ex_double_t* x;
    } x;

    x.__x = &__x;
    return (x.x->exponent == 0x7ff && (x.x->mantissah == 0 && x.x->mantissal == 0));
}

static
__inline
int
_isnan(double __x)
{
    union
    {
        double* __x;
        ex_double_t* x;
    } x;
    x.__x = &__x;
    return (x.x->exponent == 0x7ff && (x.x->mantissah != 0 || x.x->mantissal != 0));
}


static
__inline
int
do_div(long long* n, int base)
{
    int a;
    a = ((unsigned long long) * n) % (unsigned)base;
    *n = ((unsigned long long) * n) / (unsigned)base;
    return a;
}


static int skip_atoi(const char** s)
{
    int i = 0;

    while (base::memory::_isdigit(**s))
        i = i * 10 + *((*s)++) - '0';
    return i;
}

static char*
number(char* buf, char* end, long long num, int base, int size, int precision, int type)
{
    char c, sign, tmp[66];
    const char* digits;
    const char* small_digits = (new std::string(xorstr_("0123456789abcdefghijklmnopqrstuvwxyz")))->data();
    const char* large_digits = (new std::string(xorstr_("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ")))->data();
    int i;

    digits = (type & LARGE) ? large_digits : small_digits;
    if (type & LEFT)
        type &= ~ZEROPAD;
    if (base < 2 || base > 36)
        return 0;
    c = (type & ZEROPAD) ? '0' : ' ';
    sign = 0;
    if (type & SIGN) {
        if (num < 0) {
            sign = '-';
            num = -num;
            size--;
        }
        else if (type & PLUS) {
            sign = '+';
            size--;
        }
        else if (type & SPACE) {
            sign = ' ';
            size--;
        }
    }

    if ((type & SPECIAL) && ((type & REMOVEHEX) == 0)) {
        if (base == 16)
            size -= 2;

    }
    i = 0;
    if ((num == 0) && (precision != 0))
        tmp[i++] = '0';
    else while (num != 0)
        tmp[i++] = digits[do_div(&num, base)];
    if (i > precision)
        precision = i;
    size -= precision;
    if (!(type & (ZEROPAD + LEFT))) {
        while (size-- > 0) {
            if (buf <= end)
                *buf = ' ';
            ++buf;
        }
    }
    if (sign) {
        if (buf <= end)
            *buf = sign;
        ++buf;
    }

    if ((type & SPECIAL) && ((type & REMOVEHEX) == 0)) {
        if (base == 16) {
            if (buf <= end)
                *buf = '0';
            ++buf;
            if (buf <= end)
                *buf = digits[33];
            ++buf;
        }
    }

    if (!(type & LEFT)) {
        while (size-- > 0) {
            if (buf <= end)
                *buf = c;
            ++buf;
        }
    }
    while (i < precision--) {
        if (buf <= end)
            *buf = '0';
        ++buf;
    }
    while (i-- > 0) {
        if (buf <= end)
            *buf = tmp[i];
        ++buf;
    }
    while (size-- > 0) {
        if (buf <= end)
            *buf = ' ';
        ++buf;
    }

    return buf;
}

static char*
numberf(char* buf, char* end, double num, int base, int size, int precision, int type)
{
    char c, sign, tmp[66];
    const char* digits;
    const char* small_digits = (new std::string(xorstr_("0123456789abcdefghijklmnopqrstuvwxyz")))->data();
    const char* large_digits = (new std::string(xorstr_("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ")))->data();
    int i;
    long long x;

    /* FIXME
       the float version of number is direcly copy of number
    */

    digits = (type & LARGE) ? large_digits : small_digits;
    if (type & LEFT)
        type &= ~ZEROPAD;
    if (base < 2 || base > 36)
        return 0;
    c = (type & ZEROPAD) ? '0' : ' ';
    sign = 0;
    if (type & SIGN) {
        if (num < 0) {
            sign = '-';
            num = -num;
            size--;
        }
        else if (type & PLUS) {
            sign = '+';
            size--;
        }
        else if (type & SPACE) {
            sign = ' ';
            size--;
        }
    }
    if (type & SPECIAL) {
        if (base == 16)
            size -= 2;
        else if (base == 8)
            size--;
    }
    i = 0;
    if (num == 0)
        tmp[i++] = '0';
    else while (num != 0)
    {
        x = num;
        tmp[i++] = digits[do_div(&x, base)];
        num = x;
    }
    if (i > precision)
        precision = i;
    size -= precision;
    if (!(type & (ZEROPAD + LEFT))) {
        while (size-- > 0) {
            if (buf <= end)
                *buf = ' ';
            ++buf;
        }
    }
    if (sign) {
        if (buf <= end)
            *buf = sign;
        ++buf;
    }
    if (type & SPECIAL) {
        if (base == 8) {
            if (buf <= end)
                *buf = '0';
            ++buf;
        }
        else if (base == 16) {
            if (buf <= end)
                *buf = '0';
            ++buf;
            if (buf <= end)
                *buf = digits[33];
            ++buf;
        }
    }
    if (!(type & LEFT)) {
        while (size-- > 0) {
            if (buf <= end)
                *buf = c;
            ++buf;
        }
    }
    while (i < precision--) {
        if (buf <= end)
            *buf = '0';
        ++buf;
    }
    while (i-- > 0) {
        if (buf <= end)
            *buf = tmp[i];
        ++buf;
    }
    while (size-- > 0) {
        if (buf <= end)
            *buf = ' ';
        ++buf;
    }
    return buf;
}

static char* string(char* buf, char* end, const char* s, int len, int field_width, int precision, int flags)
{
    int i;
    char c;

    c = (flags & ZEROPAD) ? '0' : ' ';

    if (s == NULL)
    {
        s = xorstr_("<NULL>");
        len = 6;
    }
    else
    {
        if (len == -1)
        {
            len = 0;
            while ((unsigned int)len < (unsigned int)precision && s[len])
                len++;
        }
        else
        {
            if ((unsigned int)len > (unsigned int)precision)
                len = precision;
        }
    }
    if (!(flags & LEFT))
        while (len < field_width--)
        {
            if (buf <= end)
                *buf = c;
            ++buf;
        }
    for (i = 0; i < len; ++i)
    {
        if (buf <= end)
            *buf = *s++;
        ++buf;
    }
    while (len < field_width--)
    {
        if (buf <= end)
            *buf = ' ';
        ++buf;
    }
    return buf;
}

static char* stringw(char* buf, char* end, const wchar_t* sw, int len, int field_width, int precision, int flags)
{
    int i;
    char c;

    c = (flags & ZEROPAD) ? '0' : ' ';

    if (sw == NULL)
    {
        sw = xorstr_(L"<NULL>");
        len = 6;
    }
    else
    {
        if (len == -1)
        {
            len = 0;
            while ((unsigned int)len < (unsigned int)precision && sw[len])
                len++;
        }
        else
        {
            if ((unsigned int)len > (unsigned int)precision)
                len = precision;
        }
    }
    if (!(flags & LEFT))
        while (len < field_width--)
        {
            if (buf <= end)
                *buf = c;
            buf++;
        }
    for (i = 0; i < len; ++i)
    {
        if (buf <= end)
            *buf = (unsigned char)(*sw++);
        buf++;
    }
    while (len < field_width--)
    {
        if (buf <= end)
            *buf = ' ';
        buf++;
    }
    return buf;
}

int __cdecl crc32_vsnprintf(char* buf, size_t cnt, const char* fmt, va_list args)
{
    int len;
    unsigned long long num;
    double _double;

    int base;
    char* str, * end;
    const char* s;
    const wchar_t* sw;

    int flags;      /* flags to number() */

    int field_width;    /* width of output field */
    int precision;      /* min. # of digits for integers; max
                   number of chars for from string */
    int qualifier;      /* 'h', 'l', 'L', 'I' or 'w' for integer fields */

    /* clear the string buffer with zero so we do not need NULL terment it at end */

    str = buf;
    end = buf + cnt - 1;
    if (end < buf - 1) {
        end = ((char*)-1);
        cnt = end - buf + 1;
    }

    for (; *fmt; ++fmt) {
        if (*fmt != '%') {
            if (str <= end)
                *str = *fmt;
            ++str;
            continue;
        }

        /* process flags */
        flags = 0;
    repeat:
        ++fmt;      /* this also skips first '%' */
        switch (*fmt) {
        case '-': flags |= LEFT; goto repeat;
        case '+': flags |= PLUS; goto repeat;
        case ' ': flags |= SPACE; goto repeat;
        case '#': flags |= SPECIAL; goto repeat;
        case '0': flags |= ZEROPAD; goto repeat;
        }

        /* get field width */
        field_width = -1;
        if (base::memory::_isdigit(*fmt))
            field_width = skip_atoi(&fmt);
        else if (*fmt == '*') {
            ++fmt;
            /* it's the next argument */
            field_width = va_arg(args, int);
            if (field_width < 0) {
                field_width = -field_width;
                flags |= LEFT;
            }
        }

        /* get the precision */
        precision = -1;
        if (*fmt == '.') {
            ++fmt;
            if (base::memory::_isdigit(*fmt))
                precision = skip_atoi(&fmt);
            else if (*fmt == '*') {
                ++fmt;
                /* it's the next argument */
                precision = va_arg(args, int);
            }
            if (precision < 0)
                precision = 0;
        }

        /* get the conversion qualifier */
        qualifier = -1;
        if (*fmt == 'h' || *fmt == 'l' || *fmt == 'L' || *fmt == 'w') {
            qualifier = *fmt;
            ++fmt;
        }
        else if (*fmt == 'I' && *(fmt + 1) == '6' && *(fmt + 2) == '4') {
            qualifier = *fmt;
            fmt += 3;
        }
        else if (*fmt == 'I' && *(fmt + 1) == '3' && *(fmt + 2) == '2') {
            qualifier = 'l';
            fmt += 3;
        }
        else if (*fmt == 'F' && *(fmt + 1) == 'p') {
            fmt += 1;
            flags |= REMOVEHEX;
        }

        /* default base */
        base = 10;

        switch (*fmt) {
        case 'c': /* finished */
            if (qualifier == 'l' || qualifier == 'w') {
                wchar_t sw1[2];
                /* print unicode string */
                sw1[0] = (wchar_t)va_arg(args, int);
                sw1[1] = 0;
                str = stringw(str, end, (wchar_t*)&sw1, -1, field_width, precision, flags);
            }
            else {
                char s1[2];
                /* print ascii string */
                s1[0] = (unsigned char)va_arg(args, int);
                s1[1] = 0;
                str = string(str, end, (char*)&s1, -1, field_width, precision, flags);
            }
            continue;

        case 'C': /* finished */
            if (!(flags & LEFT))
                while (--field_width > 0) {
                    if (str <= end)
                        *str = ' ';
                    ++str;
                }
            if (qualifier == 'h') {
                if (str <= end)
                    *str = (unsigned char)va_arg(args, int);
                ++str;
            }
            else {
                if (str <= end)
                    *str = (unsigned char)(wchar_t)va_arg(args, int);
                ++str;
            }
            while (--field_width > 0) {
                if (str <= end)
                    *str = ' ';
                ++str;
            }
            continue;

        case 's': /* finished */
            if (qualifier == 'l' || qualifier == 'w') {
                /* print unicode string */
                sw = va_arg(args, wchar_t*);
                str = stringw(str, end, sw, -1, field_width, precision, flags);
            }
            else {
                /* print ascii string */
                s = va_arg(args, char*);
                str = string(str, end, s, -1, field_width, precision, flags);
            }
            continue;

        case 'S':
            if (qualifier == 'h') {
                /* print ascii string */
                s = __crt_va_arg(args, char*);
                str = string(str, end, s, -1, field_width, precision, flags);
            }
            else {
                /* print unicode string */
                sw = __crt_va_arg(args, wchar_t*);
                str = stringw(str, end, sw, -1, field_width, precision, flags);
            }
            continue;

        case 'Z':
            if (qualifier == 'w') {
                /* print counted unicode string */
                PUNICODE_STRING pus = va_arg(args, PUNICODE_STRING);
                if ((pus == NULL) || (pus->Buffer == NULL)) {
                    sw = NULL;
                    len = -1;
                }
                else {
                    sw = pus->Buffer;
                    len = pus->Length / sizeof(WCHAR);
                }
                str = stringw(str, end, sw, len, field_width, precision, flags);
            }
            else {
                /* print counted ascii string */
                PANSI_STRING pus = va_arg(args, PANSI_STRING);
                if ((pus == NULL) || (pus->Buffer == NULL)) {
                    s = NULL;
                    len = -1;
                }
                else {
                    s = pus->Buffer;
                    len = pus->Length;
                }
                str = string(str, end, s, len, field_width, precision, flags);
            }
            continue;

        case 'p':
            if ((flags & LARGE) == 0)
                flags |= LARGE;

            if (field_width == -1) {
                field_width = 2 * sizeof(void*);
                flags |= ZEROPAD;
            }
            str = number(str, end,
                (ULONG_PTR)va_arg(args, void*), 16,
                field_width, precision, flags);
            continue;

        case 'n':
            /* FIXME: What does C99 say about the overflow case here? */
            if (qualifier == 'l') {
                long* ip = va_arg(args, long*);
                *ip = (str - buf);
            }
            else {
                int* ip = va_arg(args, int*);
                *ip = (str - buf);
            }
            continue;

            /* float number formats - set up the flags and "break" */
        case 'e':
        case 'E':
        case 'f':
        case 'g':
        case 'G':
            _double = (double)va_arg(args, double);
            if (_isnan(_double)) {
                s = xorstr_("Nan");
                len = 3;
                while (len > 0) {
                    if (str <= end)
                        *str = *s++;
                    ++str;
                    len--;
                }
            }
            else if (_isinf(_double) < 0) {
                s = xorstr_("-Inf");
                len = 4;
                while (len > 0) {
                    if (str <= end)
                        *str = *s++;
                    ++str;
                    len--;
                }
            }
            else if (_isinf(_double) > 0) {
                s = xorstr_("+Inf");
                len = 4;
                while (len > 0) {
                    if (str <= end)
                        *str = *s++;
                    ++str;
                    len--;
                }
            }
            else {
                if (precision == -1)
                    precision = 6;
                str = numberf(str, end, (int)_double, base, field_width, precision, flags);
            }

            continue;


            /* integer number formats - set up the flags and "break" */
        case 'o':
            base = 8;
            break;

        case 'b':
            base = 2;
            break;

        case 'X':
            flags |= LARGE;
        case 'x':
            base = 16;
            break;

        case 'd':
        case 'i':
            flags |= SIGN;
        case 'u':
            break;

        default:
            if (*fmt) {
                if (str <= end)
                    *str = *fmt;
                ++str;
            }
            else
                --fmt;
            continue;
        }

        if (qualifier == 'I')
            num = va_arg(args, unsigned long long);
        else if (qualifier == 'l') {
            if (flags & SIGN)
                num = va_arg(args, long);
            else
                num = va_arg(args, unsigned long);
        }
        else if (qualifier == 'h') {
            if (flags & SIGN)
                num = va_arg(args, int);
            else
                num = va_arg(args, unsigned int);
        }
        else {
            if (flags & SIGN)
                num = va_arg(args, int);
            else
                num = va_arg(args, unsigned int);
        }
        str = number(str, end, num, base, field_width, precision, flags);
    }
    if (str <= end)
        *str = '\0';
    else if (cnt > 0)
        /* don't write out a null byte if the buf size is zero */
        *end = '\0';
    return str - buf;
}
