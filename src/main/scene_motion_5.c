/* scene_motion_5: 9 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02017938 @ 0x02017938, 0x2 bytes, Thumb
 * func_020178a0 @ 0x020178a0, 0x98 bytes, Thumb
 * func_0201786c @ 0x0201786c, 0x32 bytes, Thumb
 * func_020177e0 @ 0x020177e0, 0x8c bytes, Thumb
 * func_02017790 @ 0x02017790, 0x50 bytes, Thumb
 * func_02017710 @ 0x02017710, 0x80 bytes, Thumb
 * func_020176bc @ 0x020176bc, 0x54 bytes, Thumb
 * func_02017674 @ 0x02017674, 0x48 bytes, Thumb
 * func_02017654 @ 0x02017654, 0x20 bytes, Thumb
 */

extern void *func_02019de4(void *param1);
extern void func_02057bb8(unsigned short *out);
extern int func_02057bd4(void);
extern void func_02057cb8(void *p);
extern void func_02016764(void *a, void *b, int c, unsigned short d, int e, int f, int g, int h);
extern int func_02091230(int a, void *b, int c, int d);
extern int func_0200442c(void *a, int b, int c, int d);
extern void func_02019af0(void *a, int b);
extern void func_020199ec(void *a, void *b, void *c);
extern int func_02017f1c(void *a, void *b, int c, int d, int e);
extern int func_02057d0c(int, int);
extern int func_020164a0(int, int);
extern void func_02054768(int, int, int);
extern unsigned short data_020c80f8;
extern int func_020164cc(void *ptr, int);
extern int func_02057b90(int, int);
extern int func_02095a28(void);
extern int func_02057d34(void *);

void func_02017938(void) {}

int func_020178a0(void *param1, char *param2)
{
    char *r6;
    unsigned short vbuf[1];
    int val;

    r6 = (char *) func_02019de4(param1);

    func_02057bb8(vbuf);
    val = vbuf[0];
    *(unsigned short *) (r6 + 0x22) = val;

    if (func_02057bd4() != 0) {
        func_02057cb8(param2);
    }

    func_02016764((void *) (param2 + 0x334), param2, 0x28, (*(volatile unsigned short *) &data_020c80f8), 1, 0x1000, 0, 0);

    func_02091230(0x61, (void *) (param2 + 0x5c), 0, 0);
    func_0200442c((void *) (param2 + 0x514), 0x76, 0x7f, 0);

    func_02019af0(param1, 0);

    *(unsigned char *) ((char *) param1 + 4) = 0x14;
    *(unsigned char *) ((char *) param1 + 5) = (unsigned char) (*(int *) ((char *) param1 + 0x14));

    func_020199ec(param1, (char *) param1 + 6, r6 + 0x22);

    return 1;
}

void func_0201786c(void *a, void *b)
{
    int c;
    int d;

    c = (int) func_02019de4((void *) ((int) a));
    d = c + 0x22;
    if (func_02017f1c(a, b, d, 0x28, 1) != 0) {
        func_02019af0(a, 1);
    }
}

int func_020177e0(int a, int b)
{
    if (func_02057bd4() && func_02057d0c(5, b)) {
        func_02016764((void *) (b + 0x334), (void *) b, 0x27, data_020c80f8, 1, 0x1000, 0, 0);
        func_0200442c((void *) (b + 0x514), 0x4f, 0x7f, 0);
        if (func_020164a0(b + 0x334, 1) == 0x139) {
            func_02054768(b + 0xec, 0, 0);
        }
        func_02019af0((void *) a, 0);
    }
    return 1;
}

void func_02017790(void *param0, void *param1)
{
    if (func_020164cc((char *) param1 + 0x334, (int) param1) != 0) {
        func_02057cb8(param1);
        func_02016764((char *) param1 + 0x334, param1, 0, data_020c80f8, 0, 0x1000, 0, 0);
        func_02019af0(param0, 1);
    }
}

int func_02017710(int r0, int r1)
{
    int r5 = r0;
    int r4 = r1;
    int sp[5];
    int r0_2;
    int r0_3;
    int r0_4;

    if (func_02057bd4() != 0) {
        if (func_02057d0c(7, r4) != 0) {
            sp[0] = 3;
            sp[1] = 0x1000;
            sp[2] = 0;
            sp[3] = 0;
            r0_2 = ((int) (func_02016764((void *) (r4 + 0x334), (void *) r4, 0x26, data_020c80f8, sp[0], sp[1], sp[2], sp[3]),
                           r4 + 0x334));
            r0_3 = func_020164a0(r4 + 0x334, 1);
            if (r0_3 == 0x139) {
                func_02054768(r4 + 0xec, 0, 0);
            }
            func_02057b90(5, r4);
            func_02019af0((void *) r5, 0);
        }
    }
    return 1;
}

void func_020176bc(char *param1, char *param2)
{
    int a;

    a = func_020164cc(param2 + 0x334, (int) param2);
    if (a != 0) {
        if (func_02095a28() != 0) {
            func_02016764(param2 + 0x334, param2, 0x23, data_020c80f8, 0, 0x1000, 0, 0);
            param1[0x98] = 1;
        }
    }
}

void func_02017674(void *arg0, void *arg1)
{
    if (func_02057d34(arg1) != 0) {
        return;
    } else {
        func_02016764((void *) ((int) arg1 + 0x334), (void *) ((int) arg1), 0, data_020c80f8, 0, 0x1000, 0, 0);
        ((char *) arg0)[0x98] = 2;
    }
}

void func_02017654(void *arg0, void *event)
{
    int val;
    void *pvVar2;

    val = func_02057bd4();
    if (val == 0) {
        func_02019af0(arg0, 1);
        pvVar2 = (void *) ((int) arg0 + 0x98);
        *(unsigned char *) pvVar2 = 3;
    }
    return;
}
