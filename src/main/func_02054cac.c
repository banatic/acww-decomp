/* func_02054cac @ 0x02054cac, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02056e60(void *addr, int value);
extern void func_02055060(void *a, int b, int d, int e, unsigned short f, unsigned short g);

void func_02054cac(unsigned char *a, int b, int c, int d, int e, unsigned short f, unsigned short g)
{
    func_02056e60(a + 0xb8, c);
    func_02055060(a, b, d, e, f, g);
}
