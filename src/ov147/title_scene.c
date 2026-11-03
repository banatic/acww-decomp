/* title_scene: 14 functions, module ov147
 * mwccarm 1.2/base -O4,s
 * func_ov147_02299d18 @ 0x02299d18, 0x8 bytes, Thumb
 * func_ov147_02299cd0 @ 0x02299cd0, 0x48 bytes, Thumb
 * func_ov147_02299cc8 @ 0x02299cc8, 0x8 bytes, Thumb
 * func_ov147_02299c80 @ 0x02299c80, 0x48 bytes, Thumb
 * func_ov147_02299c78 @ 0x02299c78, 0x8 bytes, Thumb
 * func_ov147_02299c34 @ 0x02299c34, 0x44 bytes, Thumb
 * func_ov147_02299c2c @ 0x02299c2c, 0x8 bytes, Thumb
 * func_ov147_02299be8 @ 0x02299be8, 0x44 bytes, Thumb
 * func_ov147_02299be0 @ 0x02299be0, 0x8 bytes, Thumb
 * func_ov147_02299b98 @ 0x02299b98, 0x48 bytes, Thumb
 * func_ov147_02299b90 @ 0x02299b90, 0x8 bytes, Thumb
 * func_ov147_02299b4c @ 0x02299b4c, 0x44 bytes, Thumb
 * func_ov147_02299b44 @ 0x02299b44, 0x8 bytes, Thumb
 * func_ov147_02299b00 @ 0x02299b00, 0x44 bytes, Thumb
 */

struct UnkStruct_02299cd0 {
    int a;
    int b;
};

struct UnkStruct_02299c80 {
    int unk_00;
    int unk_04;
};

typedef struct {
    int pad_00;
    int unk_04;
} Work;

typedef struct {
    int unk_00;
    int unk_04;
} Res;

typedef struct UnkStruct_02299b98 {
    int pad_00;
    int unk_04;
} UnkStruct_02299b98;

extern void func_ov147_0229a000(void *argument0);
extern unsigned char data_021c75b8;
extern int func_020b5e10(void);
extern int func_020b6434(int, int, int, int);
extern void func_020a1930(void);
extern void func_020a1924(void);
extern void func_ov147_0229a01c(void *param);
extern void *func_020682e0(int);
extern void func_02068320(void *);
extern void func_020a1888(void);
extern void func_020a53ec(int value, int first, int second, int extra);

void func_ov147_02299d18(void *argument0)
{
    func_ov147_0229a000(argument0);
}

void func_ov147_02299cd0(int self)
{
    unsigned int cond = (data_021c75b8 == 2) ? 1 : 0;
    if (cond > 0) {
        struct UnkStruct_02299cd0 *p = (struct UnkStruct_02299cd0 *) func_020682e0(0);
        if (p->b != 0) {
            return;
        }
        ((void) (func_020b6434(((void) (func_02068320((void *) p)), func_020b5e10()), 46, 2, 3)), func_020a1930());
        func_ov147_0229a01c((void *) self);
    }
}

void func_ov147_02299cc8(void *argument0)
{
    func_ov147_0229a000(argument0);
}

void func_ov147_02299c80(void *param)
{
    unsigned int flag;
    struct UnkStruct_02299c80 *p;

    flag = (data_021c75b8 == 2) ? 1 : 0;
    if (flag != 0) {
        p = (struct UnkStruct_02299c80 *) func_020682e0(0);
        if (p->unk_04 == 0) {
            func_020b6434(((void) (func_02068320((void *) p)), func_020b5e10()), 0x2e, 2, 3);
            func_020a1924();
            func_ov147_0229a01c(param);
        }
    }
}

void func_ov147_02299c78(void *argument0)
{
    func_ov147_0229a000(argument0);
}

void func_ov147_02299c34(void *a)
{
    Work *p;
    unsigned int cond;
    p = (Work *) func_020682e0(0);
    cond = (data_021c75b8 == 2);
    if (cond && p->unk_04 == 0) {
        func_02068320(p);
        func_020b6434(func_020b5e10(), 6, 2, 2);
        func_ov147_0229a01c(a);
    }
}

void func_ov147_02299c2c(void *argument0)
{
    func_ov147_0229a000(argument0);
}

void func_ov147_02299be8(void *self)
{
    Res *res;
    unsigned int flag;

    flag = (data_021c75b8 == 2) ? 1 : 0;
    if (flag > 0) {
        res = (Res *) func_020682e0(0);
        if (res->unk_04 == 0) {
            func_02068320((void *) res);
            func_020b6434(func_020b5e10(), 0x2d, 2, 0);
            func_ov147_0229a01c(self);
        }
    }
}

void func_ov147_02299be0(void *argument0)
{
    func_ov147_0229a000(argument0);
}

void func_ov147_02299b98(void *self)
{
    unsigned int flag = (data_021c75b8 == 2) ? 1 : 0;
    if (flag > 0) {
        UnkStruct_02299b98 *p = (UnkStruct_02299b98 *) func_020682e0(0);
        if (p->unk_04 == 0) {
            func_02068320((void *) p);
            func_020b6434(func_020b5e10(), 0x2e, 2, 3);
            func_020a1888();
            func_ov147_0229a01c(self);
        }
    }
}

void func_ov147_02299b90(void *argument0)
{
    func_ov147_0229a000(argument0);
}

void func_ov147_02299b4c(void *self)
{
    void *a;
    unsigned int cond;

    a = func_020682e0(0);
    cond = (data_021c75b8 == 2);
    if (cond != 0) {
        if (*(int *) ((char *) a + 4) == 0) {
            void *c;

            func_02068320(a);
            c = (void *) func_020b5e10();
            func_020b6434((int) c, 0x30, 2, 2);
            func_ov147_0229a01c(self);
        }
    }
}

void func_ov147_02299b44(void *argument0)
{
    func_ov147_0229a000(argument0);
}

void func_ov147_02299b00(void *arg)
{
    int *result;
    unsigned int cond;

    result = (int *) func_020682e0(0);
    cond = (data_021c75b8 == 2) ? 1 : 0;
    if (cond != 0) {
        if (result[1] == 0) {
            func_02068320(result);
            func_020a53ec(2, 2, 0, 0);
            func_ov147_0229a01c(arg);
        }
    }
}
