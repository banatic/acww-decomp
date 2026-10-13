/* func_020199ec @ 0x020199ec, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020778b0(int a, unsigned short b, void *c);

void func_020199ec(int a, int b, void *c)
{
    func_020778b0(b, *(unsigned short *) c, c);
}
