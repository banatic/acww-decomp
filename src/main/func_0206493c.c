/* func_0206493c @ 0x0206493c, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02064980(int, int, int, const char *, char *);

void func_0206493c(const char *fmt, ...)
{
    char *ap;
    ap = (char *) (((unsigned int) &fmt) & ~3u) + 4;
    func_02064980(0, 4, 0, fmt, ap);
}
