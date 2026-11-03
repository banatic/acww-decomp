/* face_anim_slots: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0205d8a0 @ 0x0205d8a0, 0xc bytes, Thumb
 * func_0205d894 @ 0x0205d894, 0xc bytes, Thumb
 * func_0205d7b8 @ 0x0205d7b8, 0xdc bytes, Thumb
 * func_0205d74c @ 0x0205d74c, 0x6c bytes, Thumb
 */

extern int func_0205d8ac(int a, int b);
extern struct Work {
    int pad_00;
} data_021c9d7c;
extern int func_0205daac(int);
extern int func_0205d968(struct Work *, unsigned char, int);
extern int func_0205d978(struct Work *, int, int);
extern int func_0205d918(struct Work *, int);
extern int func_0205d908(struct Work *, int, int);
extern int func_0205dad0(void);
extern int func_0205dab8(void);
extern void MI_CpuCopy8(int, int, int);
extern void func_0205d950(struct Work *, unsigned char, int, int);
extern void func_0205d8f4(struct Work *, unsigned char, int, int);
extern int func_0205dad8(int);
extern int func_02064af4(int, int, int);

int func_0205d8a0(int a)
{
    return func_0205d8ac(a, 0);
}

int func_0205d894(int p0)
{
    return func_0205d8ac(p0, 1);
}

void func_0205d7b8(unsigned char *p, int a1, int a2, int a3)
{
    unsigned char b;
    int r4, sp8, sp4, r7, v;

    b = *p;
    r4 = func_0205daac(a1);
    if (a3 == 0) {
        if (func_0205d968(&data_021c9d7c, b, r4) == a1) {
            return;
        }
    }
    sp8 = func_0205d978(&data_021c9d7c, b, r4);
    if (r4 == 0) {
        sp4 = func_0205dad0();
    } else {
        sp4 = func_0205dab8() - func_0205dad0();
    }
    if (a2 != 0) {
        r7 = func_0205d918(&data_021c9d7c, a1);
        if (r7 != 9) {
            v = func_0205d978(&data_021c9d7c, r7, r4);
            r7 = func_0205d908(&data_021c9d7c, r7, r4);
            if (v != 0 && r7 != 0) {
                MI_CpuCopy8(v, sp8, r7);
                func_0205d950(&data_021c9d7c, b, r4, a1);
                func_0205d8f4(&data_021c9d7c, b, r4, r7);
            }
        }
    }
    r7 = func_02064af4(func_0205dad8(a1), sp8, sp4);
    if (r7 != 0) {
        func_0205d950(&data_021c9d7c, b, r4, a1);
        func_0205d8f4(&data_021c9d7c, b, r4, r7);
    }
}

void func_0205d74c(unsigned char *obj, int a, int b, int c, int d)
{
    unsigned char ch;

    ch = obj[0];

    if (a >= 0x16f) {
        func_0205d950((struct Work *) (((int *) &data_021c9d7c)), ch, 0, 0x16f);
        func_0205d8f4((struct Work *) (((int *) &data_021c9d7c)), ch, 0, 0);
    } else {
        func_0205d7b8((unsigned char *) obj, a, c, d);
    }

    if (b >= 0x16f) {
        func_0205d950((struct Work *) (((int *) &data_021c9d7c)), ch, 1, 0x16f);
        func_0205d8f4((struct Work *) (((int *) &data_021c9d7c)), ch, 1, 0);
    } else {
        func_0205d7b8((unsigned char *) obj, b, c, d);
    }
}
