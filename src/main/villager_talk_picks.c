/* villager_talk_picks: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02026528 @ 0x02026528, 0x5c bytes, Thumb
 * func_020264b4 @ 0x020264b4, 0x74 bytes, Thumb
 */

extern int func_0207cc54(int a, int b, int c);
extern void func_02063414(void *dst, int a, int b, int c, int d, int e, int f, int g, int h, int i);
extern int func_020984e8(void);

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

void func_020264b4(unsigned short *out, const unsigned char *p, int arg2)
{
    unsigned short bits;
    int count;
    int i;
    int result;
    unsigned short buf[2];

    *out = 0xfff1;
    bits = 0;
    count = 0;

    for (i = 0; i < 10; i++) {
        if (i != p[1]) {
            bits = (unsigned short) (bits | (1 << i));
            count++;
        }
    }

    result = func_020984e8();
    func_02026528(buf, bits, count, result, 1, arg2);

    *out = buf[0];
    if (*out == 0xfff1) {
        func_02026528(buf + 1, bits, count, 0, 0, arg2);
        *out = buf[1];
    }
}
