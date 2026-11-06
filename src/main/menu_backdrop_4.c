/* menu_backdrop_4: 14 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0206f28c @ 0x0206f28c, 0x64 bytes, Thumb
 * func_0206f278 @ 0x0206f278, 0x14 bytes, Thumb
 * func_0206f258 @ 0x0206f258, 0x20 bytes, Thumb
 * func_0206f244 @ 0x0206f244, 0x14 bytes, Thumb
 * func_0206f190 @ 0x0206f190, 0xb4 bytes, Thumb
 * func_0206f170 @ 0x0206f170, 0x1e bytes, Thumb
 * func_0206f150 @ 0x0206f150, 0x1e bytes, Thumb
 * func_0206f0d4 @ 0x0206f0d4, 0x7c bytes, Thumb
 * func_0206efd4 @ 0x0206efd4, 0x100 bytes, Thumb
 * func_0206efc0 @ 0x0206efc0, 0x14 bytes, Thumb
 * func_0206ef98 @ 0x0206ef98, 0x28 bytes, Thumb
 * func_0206ef8c @ 0x0206ef8c, 0xc bytes, Thumb
 * func_0206ef70 @ 0x0206ef70, 0x1c bytes, Thumb
 * func_0206ef34 @ 0x0206ef34, 0x3c bytes, Thumb
 */

extern unsigned short data_021cfc1c;
extern unsigned char data_021cfc14;
extern unsigned char data_027e0438[0x18];
extern unsigned char data_027e0434;
extern unsigned int data_021cfc2c;
extern unsigned int func_01ffccf4;
extern int func_0205c024(void *, void *, void (*)(void), int);
extern void func_0206f38c(void);
extern void func_02001ca0(int, int, int, int);
extern int func_020984e8(void);
extern unsigned int data_021fbe94;
extern void *func_020e9958(unsigned int, int);
extern int func_0203d064(void *, void *, int);
extern void *func_0203cfd0(void *);
extern void func_0206eb1c(void *, void *);
extern void *func_0203cfe4(void *);
extern void func_0200268c(void *, void *, int, int);
extern void func_020e993c(unsigned int, void *);
extern int func_020b99a0(void *, void *, int, int, int, int, void *, int);
extern void func_0209939c(int, void *);
extern void func_020029e8(int, int);
extern void func_020028bc(int, int, int, int);
extern const char data_020df2d8[];
extern const char data_020df2f8[];
extern const char data_020df310[];
extern int func_02002ca4(const char *a, int b, int c);
extern int func_02064328(char *buf, const char *fmt, unsigned char c);
extern int func_02002d14(char *buf, int a, int b, int c, int d, int e);
extern int func_02002c6c(char *buf, int a, int b, int c, int d, int e);
extern void *func_020993a8(unsigned int);
extern int func_02002bd0(void *a, void *b, int c, int d, int e);
extern int func_02002a88(void *a, void *b, int c, int d, int e);
extern void func_0206fcd4(void);
extern unsigned char data_021cfc10[];
extern unsigned char data_021cfc20[];
extern void func_0206eafc(int arg);
extern unsigned short data_021cfc18;
extern int func_0203de78(void);
extern void func_020027f0(int);
extern void func_02001ba4(int);
extern void func_0206fcc8(void);
extern void func_0206f35c(void);
extern int data_021c8c9c;

void func_0206f28c(void)
{
    int i;
    int val;

    data_021cfc1c = 0;
    if (func_0205c024(&data_021cfc2c, &func_01ffccf4, func_0206f38c, 0) != 0) {
        data_021cfc14 |= 1;
    }
    i = 0;
    val = i;
    while (i < 0x18) {
        data_027e0438[i] = val;
        i++;
    }
    func_02001ca0(1, val, 0xff, 0xc0);
    data_027e0434 = 0;
}

int func_0206f278(void)
{
    if (((*(volatile unsigned char *) &data_021cfc14) & 1) != 0) {
        return 1;
    }
    return 0;
}

int func_0206f258(void)
{
    unsigned short u;
    u = (*(unsigned short *) data_021cfc20);
    u = (unsigned short) (u + 0xfffb);
    if (u > 2) {
        return 0;
    }
    return 1;
}

int func_0206f244(void)
{
    unsigned short value;
    value = (*(volatile unsigned short *) data_021cfc20);
    if (value == 0xc) {
        return 1;
    }
    return 0;
}

void func_0206f190(unsigned short *a0, void *a1, void *a2, void *a3)
{
    int A;
    int flag;
    unsigned int v;
    unsigned int B;
    void *C;

    A = func_020984e8();
    flag = 0;
    v = *a0;
    if (v >= 0x11a8 && v <= 0x12a7) {
        flag = 1;
    }
    if (!flag) {
        if (v < 0x12a8 || v > 0x12af) {
            return;
        }
    }
    B = data_021fbe94;
    C = func_020e9958(B, 0x2c4);
    if (C == 0) {
        return;
    }

    func_0203d064(C, a0, A);
    func_0206eb1c(func_0203cfd0(C), a3);
    func_0200268c(func_0203cfe4(C), a2, 4, 4);
    func_020e993c(B, C);
    if (func_020b99a0(a1, a2, 5, 0, 0, 0xf, a3, 0) != 0) {
        func_0209939c(A, a0);
    }
}

void func_0206f170(void)
{
    func_020029e8(1, 1);
    func_020028bc(1, 0, 0, 0);
}

void func_0206f150(void)
{
    func_020029e8(5, 3);
    func_020028bc(5, 0, 0, 0);
}

int func_0206f0d4(int p)
{
    int g;
    char local[36];
    g = (*(int *) &data_021fbe94);
    if (!func_02002ca4(data_020df2d8, g, p)) {
        return 0;
    }
    func_02064328(local, data_020df2f8, (*(unsigned char *) data_021cfc10));
    if (!func_02002d14(local, g, p, 0, 0, 0)) {
        return 0;
    }
    func_02064328(local, data_020df310, (*(unsigned char *) data_021cfc10));
    func_02002c6c(local, g, p, 0, 0, 0xf);
    return 1;
}

int func_0206efd4(void *param0)
{
    int result;
    void *heap;
    int val5;
    void *p0;
    unsigned short h;
    void *p6;
    void *p7;
    void *p2;
    void *tmp1;
    void *tmp2;

    if ((*(unsigned char *) data_021cfc10) != 4) {
        return func_0206f0d4((int) param0);
    }
    heap = (*(void **) &data_021fbe94);
    val5 = func_020984e8();
    p0 = func_020993a8(val5);
    h = *(unsigned short *) p0;
    p6 = func_020e9958((unsigned int) heap, 0x200);
    if (p6 == 0) {
        return 0;
    }
    p7 = func_020e9958((unsigned int) heap, 0x20);
    if (p7 == 0) {
        func_020e993c((unsigned int) heap, p6);
        return 0;
    }
    p2 = func_020e9958((unsigned int) heap, 0x2c4);
    if (p2 == 0) {
        func_020e993c((unsigned int) heap, p6);
        func_020e993c((unsigned int) heap, p7);
        return 0;
    }
    func_0203d064(p2, &h, val5);
    tmp1 = func_0203cfd0(p2);
    func_0206eb1c(tmp1, p7);
    result = func_02002bd0(p7, param0, 0, 0, 0);
    tmp2 = func_0203cfe4(p2);
    func_0200268c(tmp2, p6, 4, 4);
    result &= func_02002a88(p6, param0, 0, 0, 0xf);
    func_020e993c((unsigned int) heap, p6);
    func_020e993c((unsigned int) heap, p7);
    func_020e993c((unsigned int) heap, p2);
    result &= func_02002ca4(data_020df2d8, (int) heap, (int) param0);
    return result;
}

void func_0206efc0(void)
{
    *(unsigned short *) ((char *) ((int) ((int *) data_021cfc20)) + (0)) = 8;
    func_0206fcd4();
}

void func_0206ef98(void)
{
    unsigned short *p_short;
    unsigned char *p_byte;

    func_0206f170();
    p_short = (unsigned short *) data_021cfc20;
    *p_short = 1;
    p_byte = (unsigned char *) data_021cfc10;
    *p_byte = 4;
    func_0206fcd4();
}

void func_0206ef8c(void)
{
    func_0206eafc(1);
}

void func_0206ef70(void)
{
    data_021cfc18 = 0;
    (*(unsigned short *) data_021cfc20) = 0;
    data_021cfc1c = 0;
}

void func_0206ef34(void)
{
    if (func_0203de78() == 0) {
        func_020027f0(1);
        func_020027f0(5);
    }
    func_02001ba4(2);
    data_021c8c9c = 0;
    func_0206fcc8();
    func_0206ef70();
    func_0206f35c();
}
