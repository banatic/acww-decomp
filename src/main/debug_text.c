/* debug_text: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b9834 @ 0x020b9834, 0x6 bytes, Thumb
 * func_020b9808 @ 0x020b9808, 0x2a bytes, Thumb
 * func_020b97e4 @ 0x020b97e4, 0x22 bytes, Thumb
 * func_020b97d4 @ 0x020b97d4, 0x10 bytes, Thumb
 * func_020b97b4 @ 0x020b97b4, 0x20 bytes, Thumb
 */

typedef char *FormatArguments;

typedef struct {
    char pad_00[2];
    unsigned short unk_02;
} Header;

extern int OS_VSNPrintf(char *, unsigned int, const char *, FormatArguments);

void func_020b9834(short *p, int a, int b)
{
    *p = (short) (a + b);
}

void func_020b9808(short *p, int q, const signed char *s)
{
    while (*s != 0) {
        func_020b9834(p, q, *s++);
        p++;
    }
}

void func_020b97e4(short *arg0, int arg1, const char *format, FormatArguments args)
{
    char local_84[0x81];

    OS_VSNPrintf(local_84, 0x81, format, args);
    func_020b9808(arg0, arg1, (const signed char *) local_84);
}

void func_020b97d4(Header *a, short *b, const char *c)
{
    func_020b9808(b, a->unk_02, (const signed char *) c);
}

void func_020b97b4(unsigned short *a, short *b, const char *format, ...)
{
    func_020b97e4(b, a[1], format, (char *) (((unsigned int) &format & ~3U) + 4U));
}
