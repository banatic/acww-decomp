/* villager_talk_object_10: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02026484 @ 0x02026484, 0x30 bytes, Thumb
 * func_02026408 @ 0x02026408, 0x7c bytes, Thumb
 */

extern void func_02063414(int, int, int, int, int, int, int, int, int, int);
extern int func_020984e8(void);

void func_02026484(int a, unsigned char *b, int c)
{
    func_02063414(a, 0x11a8, 0x100, c, 1, 0, 0, *b, 0, 1);
}

void func_02026408(unsigned short *out, unsigned char *byte, int p2)
{
    unsigned short buf[2];
    int v;

    *out = 0xfff1;
    v = func_020984e8();
    func_02063414((int) buf, 0x11a8, 0x100, p2, 1, v, 0, *byte, 0, 1);
    *out = buf[0];
    if (*out == 0xfff1) {
        v = func_020984e8();
        func_02063414((int) (buf + 1), 0x11a8, 0x100, p2, 1, v, 1, *byte, 0, 1);
        *out = buf[1];
    }
}
