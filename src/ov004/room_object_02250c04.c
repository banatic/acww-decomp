/* room_object_02250c04: 8 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0221573c @ 0x0221573c, 0x1c bytes, Thumb
 * func_ov004_02215718 @ 0x02215718, 0x24 bytes, Thumb
 * func_ov004_022156f4 @ 0x022156f4, 0x24 bytes, Thumb
 * func_ov004_022156c8 @ 0x022156c8, 0x2c bytes, Thumb
 * func_ov004_022156b0 @ 0x022156b0, 0x18 bytes, Thumb
 * func_ov004_022156a0 @ 0x022156a0, 0x10 bytes, Thumb
 * func_ov004_0221569c @ 0x0221569c, 0x4 bytes, Thumb
 * func_ov004_02215504 @ 0x02215504, 0x198 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int *unk_00;
    char pad_04[0xe8];
    int *unk_EC;
} UnkStruct_022156f4;

typedef struct {
    unsigned int unk_00;
    unsigned char pad_04[0xe8];
    unsigned int unk_EC;
} UnkStruct_022156c8;

struct UnkStruct_02215504 {
    int unk_00;
    u16 unk_04;
};

extern int func_ov004_0221152c(unsigned int size);
extern void *func_ov004_022110e4(void *);
extern char data_ov004_02250c04;
extern char data_ov004_02250cb0;
extern void *func_ov004_02210cf0(void *);
extern void func_ov004_02211518(void *self);
extern void func_ov004_0221041c(void *, int, int, int, int);
extern int func_ov004_0220ffbc(char *parameter0);
extern int func_ov004_0223cb10(void);
extern void *func_ov004_0223ca9c(int a, void *self);
extern void *func_ov004_0220e220(void *p);
extern struct UnkStruct_02215504 *func_ov004_0220da04(void *p, int i);
extern int func_ov004_0223cb20(void *o);
extern int func_ov004_0221078c(void *self);
extern void func_ov004_022101e4(void *self, int a, int b, int c, int d);
extern int func_ov004_0220ec8c(void *self);
extern int func_02095380(int v);

void *func_ov004_02215718(void *this);

void func_ov004_0221573c(void)
{
    void *conditionInput0;

    if ((conditionInput0 = (void *) (func_ov004_0221152c(0x844)))) {
        func_ov004_02215718((void *) conditionInput0);
    }
}

void *func_ov004_02215718(void *this)
{
    func_ov004_022110e4(this);
    *(void **) this = &data_ov004_02250c04;
    *(void **) ((char *) this + 0xec) = &data_ov004_02250cb0;
    return this;
}

void *func_ov004_022156f4(UnkStruct_022156f4 *obj)
{
    obj->unk_00 = ((int *) &data_ov004_02250c04);
    obj->unk_EC = ((int *) &data_ov004_02250cb0);
    func_ov004_02210cf0(obj);
    return obj;
}

UnkStruct_022156c8 *func_ov004_022156c8(UnkStruct_022156c8 *self)
{
    self->unk_00 = (unsigned int) ((unsigned int *) &data_ov004_02250c04);
    self->unk_EC = (unsigned int) ((unsigned int *) &data_ov004_02250cb0);
    func_ov004_02210cf0(self);
    func_ov004_02211518(self);
    return self;
}

int func_ov004_022156b0(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0221041c(self, 0x0, 0x0, 0x0, 0x0);
    return 0x1;
}

int func_ov004_022156a0(char *arg0)
{
    func_ov004_0220ffbc((char *) arg0);
    return 1;
}

int func_ov004_0221569c(void)
{
    return 1;
}

void func_ov004_02215504(char *self, int flag)
{
    void *o;
    int done;
    struct UnkStruct_02215504 *e;
    int r;

    o = func_ov004_0223ca9c(func_ov004_0223cb10(), self);
    done = 0;
    if (o != 0) {
        e = func_ov004_0220da04(func_ov004_0220e220(self + 0x6cc), done);
        if (*(int *) (self + 0x780) == 0x16) {
            if (func_ov004_0223cb20(o) == 2) {
                if (flag != 0) {
                    if (func_ov004_0221078c(self) != 0) {
                        done = 1;
                    }
                    func_ov004_022101e4(self, 0, 1, 0x1000, 0);
                } else {
                    if (func_ov004_0221078c(self) != 0) {
                        done = 1;
                    }
                    func_ov004_022101e4(self, 0, 3, 0x1000, (u16) (e->unk_04 - 1));
                }
            } else if (func_ov004_0223cb20(o) == 0) {
                if (flag != 0) {
                    if (func_ov004_0221078c(self) != 0) {
                        done = 1;
                    }
                    func_ov004_022101e4(self, 0, 3, 0x1000, (u16) (e->unk_04 - 1));
                } else {
                    if (func_ov004_0221078c(self) != 0) {
                        done = 1;
                    }
                    func_ov004_022101e4(self, 0, 1, 0x1000, 0);
                }
            }
        } else if (func_ov004_0223cb20(o) == 3) {
            if (flag != 0) {
                if (func_ov004_0221078c(self) != 0) {
                    done = 1;
                }
                func_ov004_022101e4(self, 0, 1, 0x1000, 0);
            } else {
                if (func_ov004_0221078c(self) != 0) {
                    done = 1;
                }
                func_ov004_022101e4(self, 0, 3, 0x1000, (u16) (e->unk_04 - 1));
            }
        } else if (func_ov004_0223cb20(o) == 1) {
            if (flag != 0) {
                if (func_ov004_0221078c(self) != 0) {
                    done = 1;
                }
                func_ov004_022101e4(self, 0, 3, 0x1000, (u16) (e->unk_04 - 1));
            } else {
                if (func_ov004_0221078c(self) != 0) {
                    done = 1;
                }
                func_ov004_022101e4(self, 0, 1, 0x1000, 0);
            }
        }
    }
    if (done == 0) {
        r = func_ov004_0220ec8c(self);
        if (r != 0xffff) {
            func_02095380(r);
        }
    }
}
