/* clock_7: 5 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02216c44 @ 0x02216c44, 0x1c bytes, Thumb
 * func_ov004_02216c20 @ 0x02216c20, 0x24 bytes, Thumb
 * func_ov004_02216bfc @ 0x02216bfc, 0x24 bytes, Thumb
 * func_ov004_02216bd0 @ 0x02216bd0, 0x2c bytes, Thumb
 * func_ov004_02216aec @ 0x02216aec, 0xe4 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int *unk_00;
    char pad_04[0xe8];
    int *unk_EC;
} UnkStruct_02216bfc;

typedef struct {
    unsigned int unk_00;
    unsigned char pad_04[0xe8];
    unsigned int unk_EC;
} UnkStruct_02216bd0;

extern int func_ov004_0221152c(unsigned int size);
extern void *func_ov004_022110e4(void *);
extern char data_ov004_02251d98;
extern char data_ov004_02251e44;
extern void *func_ov004_02210cf0(void *);
extern void func_ov004_02211518(void *self);
extern int func_ov004_0220ffa4(void *s);
extern void func_0209def4(void *p);
extern int func_0209d324(int h);
extern int func_02055140(void *p, int a);
extern int func_ov004_0220e220(void *p);
extern int func_ov004_0220da04(int a, int b);
extern void func_02055060(void *p, int a, int b, int c, int d, int e);
extern void func_02055050(void *p);
extern void func_ov004_0221041c(void *s, int a, int b, int c, int d);

void *func_ov004_02216c20(void *this);

void func_ov004_02216c44(void)
{
    void *conditionInput0;

    if ((conditionInput0 = (void *) (func_ov004_0221152c(0x84c)))) {
        func_ov004_02216c20((void *) conditionInput0);
    }
}

void *func_ov004_02216c20(void *this)
{
    func_ov004_022110e4(this);
    *(void **) this = &data_ov004_02251d98;
    *(void **) ((char *) this + 0xec) = &data_ov004_02251e44;
    return this;
}

void *func_ov004_02216bfc(UnkStruct_02216bfc *obj)
{
    obj->unk_00 = ((int *) &data_ov004_02251d98);
    obj->unk_EC = ((int *) &data_ov004_02251e44);
    func_ov004_02210cf0(obj);
    return obj;
}

UnkStruct_02216bd0 *func_ov004_02216bd0(UnkStruct_02216bd0 *self)
{
    self->unk_00 = (unsigned int) ((unsigned int *) &data_ov004_02251d98);
    self->unk_EC = (unsigned int) ((unsigned int *) &data_ov004_02251e44);
    func_ov004_02210cf0(self);
    func_ov004_02211518(self);
    return self;
}

int func_ov004_02216aec(char *s)
{
    int h;
    int st;
    h = func_ov004_0220ffa4(s);
    func_0209def4(s + 0x848);
    *(u16 *) (s + 0x846) = *(u16 *) (s + 0x848);
    *(char *) (s + 0x844) = -1;
    st = *(int *) (s + 0x780);
    if (st == 0x10) {
        if (func_02055140(s + 0x538, func_0209d324(h)) != 0) {
            func_02055060(s + 0x538, func_ov004_0220da04(func_ov004_0220e220(s + 0x6cc), 0), 1, 0x1000, 0, 0);
            func_02055050(s + 0x538);
        }
    } else if (st == 0x11) {
        if (func_02055140(s + 0x538, func_0209d324(h)) != 0) {
            func_02055060(s + 0x538, func_ov004_0220da04(func_ov004_0220e220(s + 0x6cc), 0), 0, 0x1000, 0, 0);
            func_02055050(s + 0x538);
        }
    } else if (st == 0x2b) {
        func_ov004_0221041c(s, 0, 0, 0x1000, 0);
    }
    return 1;
}
