/* func_0205d4f0 @ 0x0205d4f0, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0205d4e4(int);
extern void func_0205d3d4(int, unsigned short *, int, int, int);

void func_0205d4f0(int arg)
{
    unsigned short s;

    func_0205d4e4(arg);
    s = 0xFFF1;
    func_0205d3d4(arg, &s, 0, 0, 0);
}
