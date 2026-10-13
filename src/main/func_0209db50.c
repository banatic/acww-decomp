/* func_0209db50 @ 0x0209db50, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209df04(void *, unsigned char *, int, int);

int func_0209db50(int unused, unsigned char *b, int c, int d)
{
    unsigned int buf[2];
    buf[0] = 0;
    buf[1] = 0;
    func_0209df04(&buf, b, c, d);
    return (short) (*b - ((unsigned char *) buf)[0]);
}
