/* taxi: 10 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_02273198 @ 0x02273198, 0x1c bytes, Thumb
 * func_ov068_02273158 @ 0x02273158, 0x40 bytes, Thumb
 * func_ov068_02273144 @ 0x02273144, 0x12 bytes, Thumb
 * func_ov068_022730c8 @ 0x022730c8, 0x7c bytes, Thumb
 * func_ov068_022730ac @ 0x022730ac, 0x1c bytes, Thumb
 * func_ov068_022730a8 @ 0x022730a8, 0x2 bytes, Thumb
 * func_ov068_02273088 @ 0x02273088, 0x20 bytes, Thumb
 * func_ov068_02273030 @ 0x02273030, 0x58 bytes, Thumb
 * func_ov068_0227302c @ 0x0227302c, 0x2 bytes, Thumb
 * func_ov068_02272fe8 @ 0x02272fe8, 0x44 bytes, Thumb
 */

struct __unknown_02273198 {
    unsigned char pad_00[0x59a];
    unsigned short unk_59A;
};

typedef struct {
    char pad_00[0x598];
    unsigned short unk_598;
    short unk_59A;
} UnkStruct_022730c8;

typedef struct {
    char pad_00[0x59a];
    unsigned short unk_59A;
} Something;

extern void func_ov068_022732bc(void *p, int x);
extern int func_02056f28(void *ptr, int value);
extern void func_0200467c(int cmd);
extern int func_ov068_02273230(void *, int);
extern void *data_ov068_022787fc;
extern int func_ov004_0222c3c4(void *p, int a);
extern void func_02055060(void *p, int a, int b, int c, int d, int e);
extern int func_02054ecc(int);

int func_ov068_02273198(struct __unknown_02273198 *p)
{
    p->unk_59A = 31;
    func_ov068_022732bc(p, 0);
    return 1;
}

void func_ov068_02273158(void *param)
{
    if (func_02056f28((char *) param + 0x188, 0) != 0) {
        func_0200467c(0x886);
    } else if (func_02056f28((char *) param + 0x188, 0x1c) != 0) {
        func_0200467c(0x887);
    }
}

int func_ov068_02273144(int a)
{
    func_ov068_022732bc((void *) a, 0);
    return 1;
}

void func_ov068_022730c8(UnkStruct_022730c8 *self)
{
    if (func_02056f28((char *) self + 0x188, 0) != 0) {
        func_0200467c(0x886);
    } else if (func_02056f28((char *) self + 0x188, 0x1c) != 0) {
        func_0200467c(0x887);
    }
    if (self->unk_598 % 3 == 0) {
        if (self->unk_59A >= 0) {
            self->unk_59A--;
            if (self->unk_59A == 0) {
                func_ov068_02273230(self, 2);
            }
        }
    }
    self->unk_598++;
}

int func_ov068_022730ac(Something *obj)
{
    obj->unk_59A = 0;
    func_ov068_022732bc((void *) obj, 1);
    return 1;
}

void func_ov068_022730a8(void) {}

int func_ov068_02273088(void)
{
    void *ptr = data_ov068_022787fc;
    if (ptr != 0) {
        return func_ov068_02273230(ptr, 1);
    }
    return 1;
}

int func_ov068_02273030(void)
{
    int temp;
    if ((*(unsigned char **) &data_ov068_022787fc)) {
        (*(unsigned char **) &data_ov068_022787fc)[0x430] = 1;
        temp = func_ov004_0222c3c4((char *) (*(unsigned char **) &data_ov068_022787fc) + 0x388, 0);
        func_02055060((char *) (*(unsigned char **) &data_ov068_022787fc) + 0x2d0, temp, 1, 0x1000, 0, 0);
        return 1;
    } else {
        return 0;
    }
}

void func_ov068_0227302c(void) {}

void func_ov068_02272fe8(int unused, int p1, int p2, int p3, unsigned char p4, int p5, unsigned short p6, unsigned short p7)
{
    if (func_02054ecc(p2) != func_ov004_0222c3c4((void *) p3, p1)) {
        func_02055060((void *) p2, func_ov004_0222c3c4((void *) p3, p1), (unsigned char) p4, p5, (unsigned short) p6,
                      (unsigned short) p7);
    }
}
