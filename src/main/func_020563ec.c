/* func_020563ec @ 0x020563ec, 0x36 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020563cc(int, int, int, int);
extern void func_02056498(int, int, int, unsigned char, int, unsigned short);
extern void func_020563dc(int, int);

void func_020563ec(int a, int b, int c, int d, unsigned char e, int f, unsigned short g)
{
    func_020563cc(a, b, c, d);
    func_02056498(a, c, d, e, f, g);
    func_020563dc(a, b);
}
