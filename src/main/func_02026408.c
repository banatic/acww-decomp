/* func_02026408 @ 0x02026408, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern void func_02063414(void *dst, int a, int b, int c, int d, int e, int f, int g, int h, int i);

void func_02026408(unsigned short *out, unsigned char *byte, int p2)
{
    unsigned short buf[2];
    int v;

    *out = 0xfff1;
    v = func_020984e8();
    func_02063414(buf, 0x11a8, 0x100, p2, 1, v, 0, *byte, 0, 1);
    *out = buf[0];
    if (*out == 0xfff1) {
        v = func_020984e8();
        func_02063414(buf + 1, 0x11a8, 0x100, p2, 1, v, 1, *byte, 0, 1);
        *out = buf[1];
    }
}
