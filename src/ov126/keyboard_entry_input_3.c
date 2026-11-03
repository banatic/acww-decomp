/* keyboard_entry_input_3: 7 functions, module ov126
 * mwccarm 1.2/base -O4,s
 * func_ov126_022a01dc @ 0x022a01dc, 0x44 bytes, Thumb
 * func_ov126_022a0168 @ 0x022a0168, 0x74 bytes, Thumb
 * func_ov126_022a011c @ 0x022a011c, 0x4c bytes, Thumb
 * func_ov126_022a0110 @ 0x022a0110, 0xc bytes, Thumb
 * func_ov126_022a00a4 @ 0x022a00a4, 0x6c bytes, Thumb
 * func_ov126_022a0054 @ 0x022a0054, 0x50 bytes, Thumb
 * func_ov126_022a0000 @ 0x022a0000, 0x54 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0xad];
    unsigned char unk_AD;
    unsigned char pad_AE[0x3dc4 - 0xad - 1];
    unsigned char unk_3DC4;
} UnkStruct_022a00a4;

extern int func_ov126_022a0740(void *a);
extern void func_ov126_022a06d8(void *a);
extern void func_ov095_0229b3ec(void *p);
extern int func_ov126_022a0220(void *a, void *b);
extern void func_ov126_022a08c4(void *a);
extern void func_ov124_0229f2dc(void *, void *, unsigned char);
extern int func_ov126_0229f7c8(void *, int);
extern int func_02051d08(void *, unsigned char);
extern void func_ov124_0229f320(void *);
extern void func_ov124_0229f2e4(void *);
extern void func_ov126_0229f7b8(void *, int);
extern void func_ov126_022a0978(void *);
extern void func_ov124_0229f2c8(unsigned char *p, int a, int b, int c, int d);
extern void func_0200467c(int cmd);
extern int func_ov002_0220a620(unsigned char *ptr, int val);
extern int func_ov002_0220a784(unsigned char *ptr, int val);
extern void func_ov126_022a0ae0(UnkStruct_022a00a4 *p, int val);
extern int func_ov002_0220ab38(void *, int a1);
extern int func_ov002_0220ab84(void *, int a1);
extern void func_ov126_0229f7a8(char *, int);
extern void func_ov095_02299aec(char *);
extern int func_ov095_02299b7c(char *);
extern int func_ov095_02299b38(char *);
extern void func_ov002_0220a0b4(char *, int, int);
extern void func_ov002_0220a374(char *, int);
extern void func_ov126_0229fea0(char *);

void func_ov126_022a0168(void *self);
void func_ov126_022a011c(unsigned char *p);

int func_ov126_022a01dc(void *a, void *b)
{
    int ret;

    if (func_ov126_022a0740(a)) {
        func_ov126_022a06d8(a);
        func_ov095_0229b3ec((char *) a + 0x19c);
    }
    ret = func_ov126_022a0220(a, b);
    func_ov126_022a0168(a);
    func_ov126_022a08c4(a);
    return ret;
}

void func_ov126_022a0168(void *self)
{
    char *base = (char *) self;
    func_ov124_0229f2dc(base + 0xb0, base + 0x4248, *((unsigned char *) (base + 0xa6)));
    if (func_ov126_0229f7c8(base, 0x100) != 0) {
        int r = func_02051d08(base + 0x4248, *((unsigned char *) (base + 0xa6)));
        *(int *) (base + 0xa0) = -(*((unsigned char *) (base + 0xaf)) - r - 2);
    }
    func_ov124_0229f320(base + 0xb0);
    func_ov126_022a011c((unsigned char *) base);
    func_ov124_0229f2e4(base + 0xb0);
    func_ov126_0229f7b8(base, 0x10);
    func_ov126_022a0978(base);
}

void func_ov126_022a011c(unsigned char *p)
{
    int diff;
    int min;
    int k1;
    int k2;

    if (func_ov126_022a0740((void *) p)) {
        unsigned char a = p[0xaa];
        unsigned char b = p[0xa9];

        if (b > a) {
            min = a;
            diff = b - a;
        } else {
            min = b;
            diff = a - b;
        }
        k1 = 7;
        k2 = 6;
    } else {
        diff = 0;
    }

    if (diff != 0) {
        func_ov124_0229f2c8(p + 0xb0, k1, k2, min, diff);
    }
}

void func_ov126_022a0110(void *receiver)
{
    func_0200467c(0x34);
}

int func_ov126_022a00a4(UnkStruct_022a00a4 *p)
{
    if (p->unk_AD == 3) {
        return 0;
    }
    if (func_ov002_0220a620(&p->unk_3DC4, 6) == 0) {
        if (func_ov002_0220a784(&p->unk_3DC4, 6) != 0) {
            func_ov126_022a0ae0(p, 0);
            return 1;
        }
    }
    if (p->unk_AD != 0) {
        return 0;
    }
    if (func_ov002_0220a784(&p->unk_3DC4, 7) != 0) {
        func_ov126_022a0ae0(p, 1);
        return 1;
    }
    return 0;
}

void func_ov126_022a0054(void *self)
{
    switch (((unsigned char *) self)[0xad]) {
        case 0:
            func_ov002_0220ab38((unsigned char *) self + 0x3dc4, 0xd8);
            break;
        case 2:
            func_ov002_0220ab84((unsigned char *) self + 0x3dc4, 0x21);
            break;
        case 1:
            func_ov002_0220ab84((unsigned char *) self + 0x3dc4, 0x65);
            break;
        case 3:
            break;
    }
}

void func_ov126_022a0000(char *arg0)
{
    int val;
    int val2;

    func_ov126_0229f7a8(arg0, 0x80);
    func_ov095_02299aec(arg0 + 0x19c);
    val = func_ov095_02299b7c(arg0 + 0x19c);
    val2 = func_ov095_02299b38(arg0 + 0x19c);
    func_ov002_0220a0b4(arg0 + 0x3f90, val, val2);
    func_ov002_0220a374(arg0 + 0x3f90, 1);
    func_ov126_0229fea0(arg0);
}
