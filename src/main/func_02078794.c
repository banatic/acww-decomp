/* func_02078794 @ 0x02078794, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020789f4(int a, int b, int c);
extern unsigned short func_02077898(int a);

void func_02078794(int a, int b, unsigned short *out, int c)
{
    func_020789f4(a, b, c + 2);
    *out = func_02077898(c);
}
