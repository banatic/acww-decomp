/* func_0202678c @ 0x0202678c, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202d190(unsigned short *p1, int p2, int p3, unsigned char p4);

void func_0202678c(unsigned short *out, void *src)
{
    int zero = 0;
    *out = 0xfff1;
    if (func_0202d190(out, 1, 2, *(unsigned char *) ((char *) src + 4)) != 0) {
        return;
    }
    if (func_0202d190(out, zero, zero, *(unsigned char *) ((char *) src + 4)) != 0) {
        return;
    }
    func_0202d190(out, 3, 4, *(unsigned char *) ((char *) src + 4));
}
