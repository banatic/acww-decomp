/* func_020b97b4 @ 0x020b97b4, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef char *FormatArguments;

extern void func_020b97e4(short *, int, const char *, FormatArguments);

void func_020b97b4(unsigned short *a, short *b, const char *format, ...)
{
    func_020b97e4(b, a[1], format, (char *) (((unsigned int) &format & ~3U) + 4U));
}
