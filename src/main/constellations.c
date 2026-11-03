/* constellations: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b0fc8 @ 0x020b0fc8, 0x34 bytes, Thumb
 * func_020b0fa0 @ 0x020b0fa0, 0x28 bytes, Thumb
 * func_020b0f54 @ 0x020b0f54, 0x4c bytes, Thumb
 */

extern void func_020b0ffc(int a, unsigned short b, int c);
extern void *func_020b1498(int);
extern int func_020b1068(int);

void func_020b0fc8(int param0, char *param1, int param2)
{
    int i;
    unsigned short value;

    for (i = 0; i < 16; i++) {
        value = *(unsigned short *) (param1 + (i << 1) + 0x2a);
        if (value != 0xFFFF) {
            func_020b0ffc(param0, value, param2);
        }
    }
}

void func_020b0fa0(void *arg)
{
    int i;
    void *p;

    for (i = 0; i < 16; i++) {
        p = func_020b1498(i);
        if (p != 0) {
            func_020b0fc8((int) arg, (char *) p, 7);
        }
    }
}

void func_020b0f54(unsigned short *p)
{
    int i;
    unsigned short *q = p;
    func_020b0fa0(p);
    for (i = 0; i < 0x800; i++) {
        if (func_020b1068(*q & 0x3ff) != 0) {
            if (((*q & 0xf000) >> 12) != 7) {
                *q = 0x4010;
            }
        }
        q++;
    }
}
