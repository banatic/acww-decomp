/* func_02026528 @ 0x02026528, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0207cc54(int a, int b, int c);
extern void func_02063414(void *dst, int a, int b, int c, int d, int e, int f, int g, int h, int i);

void func_02026528(unsigned short *dest, int p2, int p3, int p4, unsigned char p5, int p6)
{
    int r;
    unsigned short buf;

    *dest = 0xfff1;
    goto test;
body:
    func_02063414(&buf, 0x11a8, 0x100, p6, 1, p4, p5, r, 0, 1);
    *dest = buf;
    goto end;
test:
    r = func_0207cc54(p2, p3, 10);
    if (r != -1) {
        goto body;
    }
end:;
}
