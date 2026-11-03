/* tailor_object_2: 7 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0222fef4 @ 0x0222fef4, 0x4 bytes, Thumb
 * func_ov004_0222fef0 @ 0x0222fef0, 0x2 bytes, Thumb
 * func_ov004_0222fed4 @ 0x0222fed4, 0x1c bytes, Thumb
 * func_ov004_0222feac @ 0x0222feac, 0x28 bytes, Thumb
 * func_ov004_0222fea8 @ 0x0222fea8, 0x4 bytes, Thumb
 * func_ov004_0222fe50 @ 0x0222fe50, 0x58 bytes, Thumb
 * func_ov004_0222fe38 @ 0x0222fe38, 0x18 bytes, Thumb
 */

typedef struct UnkStruct_0222feac UnkStruct_0222feac;

struct UnkStruct_0222feac {
    void (**vt)(UnkStruct_0222feac *, int);
};

extern int func_020e8b0c(int a, int b, int c);
extern int func_02070070(void);
extern int func_ov004_0222c2c8(void *p, int k);

int func_ov004_0222fef4(void *callbackObject)
{
    return 1;
}

void func_ov004_0222fef0(void *callbackObject) {}

int func_ov004_0222fed4(char *self)
{
    // DECLS
    // ENDDECLS
    *(int *) (self + 0x33c) = 0x1000;
    *(void **) (self + 0x43c) = 0x0;
    return 0x1;
}

void func_ov004_0222feac(UnkStruct_0222feac *self)
{
    *(int *) ((char *) self + 0x198) = 0x1000;
    *(int *) ((char *) self + 0x428) = 0x1000;
    self->vt[24](self, 2);
}

int func_ov004_0222fea8(void *callbackObject)
{
    return 1;
}

void func_ov004_0222fe50(void *self)
{
    unsigned int a = ((unsigned int) *(int *) ((char *) self + 0x334) << 4) >> 16;
    unsigned short b = (unsigned short) ((int) a / 0x38);

    if (func_020e8b0c((unsigned short) (a - b * 0x38), 0x11, 0x34) != 0 && func_02070070() == 0) {
        func_ov004_0222c2c8((char *) self + 0x250, 0x85e);
    }
}

int func_ov004_0222fe38(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self + 0x33c) = 0x0;
    *(void **) (self + 0x43c) = 0x0;
    return 0x1;
}
