/* session_net: 11 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02077b58 @ 0x02077b58, 0x16 bytes, Thumb
 * func_02077b50 @ 0x02077b50, 0x8 bytes, Thumb
 * func_02077b3c @ 0x02077b3c, 0x14 bytes, Thumb
 * func_02077b28 @ 0x02077b28, 0x12 bytes, Thumb
 * func_02077b20 @ 0x02077b20, 0x8 bytes, Thumb
 * func_02077b14 @ 0x02077b14, 0xa bytes, Thumb
 * func_02077afc @ 0x02077afc, 0x18 bytes, Thumb
 * func_02077ae8 @ 0x02077ae8, 0x14 bytes, Thumb
 * func_02077a8c @ 0x02077a8c, 0x5c bytes, Thumb
 * func_02077a80 @ 0x02077a80, 0xc bytes, Thumb
 * func_02077a64 @ 0x02077a64, 0x1c bytes, Thumb
 */

extern int func_020ec260(void);
extern int func_020e9968(void *heap, int size, int type);
extern unsigned char data_021c9b30[];
extern void func_020e993c(int, int);
extern int func_02073dd4(void *self, int idx);
extern int func_02073918(void *self, int idx);
extern int func_02073d10(void *self, int idx);
extern void *data_020ccf94;
extern int func_020ec1e8(void);

int func_02077b58(int a)
{
    int b = func_020ec260();
    if (a >= b) {
        a = a - 1;
    }
    return a;
}

void func_02077b50(unsigned char *p0, int p1)
{
    p0[0] = (p1 & 3);
}

void func_02077b3c(unsigned char *out, int a, int b)
{
    *out = (unsigned char) (((b & 0x1F) << 2) | 0x80 | (a & 3));
}

int func_02077b28(const unsigned char *byte)
{
    if (*byte & 0x80) {
        return 1;
    }
    return 0;
}

int func_02077b20(unsigned char *p0)
{
    return (p0[0] & 3);
}

int func_02077b14(unsigned char *p)
{
    return (*p >> 2) & 0x1f;
}

int func_02077afc(int size, int type)
{
    void *r0;
    int r1;
    int r2;
    int r3;

    r3 = size;
    r2 = type;
    r0 = *(void **) data_021c9b30;
    r1 = r3;
    r3 = 0x020e9968;
    return func_020e9968(r0, r1, r2);
}

void func_02077ae8(int x)
{
    func_020e993c((*(int *) data_021c9b30), x);
}

int func_02077a8c(unsigned short flags)
{
    int i = 3;
    void *p = data_020ccf94;

    for (; i >= 0; i--) {
        if (func_02073dd4(p, i) == 0) {
            continue;
        }
        if (func_02073918(p, i) != 0) {
            continue;
        }
        if (((unsigned short) (1 << i) & flags) == 0) {
            continue;
        }
        if (func_02073d10(p, i) != 0) {
            continue;
        }
        return 0;
    }
    return 1;
}

int func_02077a80(void)
{
    return func_02077a8c(15);
}

int func_02077a64(void)
{
    int mode;

    mode = func_020ec1e8();
    return (mode == 3 || mode == 4);
}
