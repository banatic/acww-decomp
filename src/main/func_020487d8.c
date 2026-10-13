/* func_020487d8 @ 0x020487d8, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020644cc(int);
extern void func_02048cb8(int, int, int, int, int, void (*)(void), int);
extern void func_02048ec8(void);
extern unsigned short data_020cabc4[];

void func_020487d8(int p0, int p1, int p2, int p3)
{
    int v1 = func_020644cc(p2);
    int v2 = func_020644cc(p3);
    int idx = func_020644cc(0xc);

    func_02048cb8(p0, p1, v1 + 1, v2 + 1, data_020cabc4[idx], func_02048ec8, 0);
}
