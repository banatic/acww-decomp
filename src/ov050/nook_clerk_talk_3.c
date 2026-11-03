/* nook_clerk_talk_3: 9 functions, module ov050
 * mwccarm 1.2/base -O4,s
 * func_ov050_02261ce4 @ 0x02261ce4, 0x44 bytes, Thumb
 * func_ov050_02261cd8 @ 0x02261cd8, 0xa bytes, Thumb
 * func_ov050_02261cb4 @ 0x02261cb4, 0x22 bytes, Thumb
 * func_ov050_02261ca0 @ 0x02261ca0, 0x14 bytes, Thumb
 * func_ov050_02261c7c @ 0x02261c7c, 0x22 bytes, Thumb
 * func_ov050_02261bb8 @ 0x02261bb8, 0xc4 bytes, Thumb
 * func_ov050_02261918 @ 0x02261918, 0x2a0 bytes, Thumb
 * func_ov050_02261908 @ 0x02261908, 0x10 bytes, Thumb
 * func_ov050_022618d0 @ 0x022618d0, 0x38 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_02261ce4 {
    char pad_00[0xCC];
    int unk_CC;
    int unk_D0;
};

struct UnkStruct_02261cd8 {
    char pad_00[0xCC];
    int unk_CC;
};

struct UnkStruct_02261ca0 {
    char pad_00[0xb4];
    int unk_B4;
    char pad_B8[0x0c];
    int unk_C4;
};

typedef struct UnkStruct_02261bb8 {
    char pad_00[0xb4];
    char *unk_B4;
    char pad_B8[0xd0 - 0xb8];
    int unk_D0;
} UnkStruct_02261bb8;

typedef struct UnkStruct_02261918 {
    char pad_00[0x732];
    u16 unk_732;
} UnkStruct_02261918;

typedef struct UnkStruct_02261918_2 {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0xb4 - 0x44];
    UnkStruct_02261918 *unk_B4;
    char pad_B8[0xd0 - 0xb8];
    int unk_D0;
} UnkStruct_02261918_2;

struct FuncOv050Obj {
    unsigned char pad_00[0x40];
    void *unk_40;
};

extern int func_020154b4(void *self, short *ptr, int arg2, int arg3, int arg4);
extern int func_0209a000(short *ptr, int arg);
extern void func_020157c8(int, int, int);
extern int func_02015828(int, int);
extern void func_ov050_02263b38(int, int);
extern void func_0201b3a4(int, int);
extern int func_0204bcdc(u16 *p);
extern int func_0204bc64(u16 *p);
extern int func_02060de4(void *tbl, u8 idx);
extern int func_020984e8(void);
extern int func_02099020(int, int);
extern void func_02098ff8(int, int);
extern int func_0202e9fc(void);
extern int func_ov050_02260510(UnkStruct_02261918 *);
extern void func_0206844c(int, void *, int);
extern char data_021f43e8[];
extern void func_02060cf4(void *ptr);
extern unsigned char data_021ebcd4[];
extern unsigned char data_ov050_022650b4[];
extern unsigned char data_ov050_02265e9c[];
int func_020683e4(void *a, int b, unsigned char *c, unsigned char *d);
int func_02060c80(unsigned char *a, unsigned char b);

void func_ov050_02261ce4(struct UnkStruct_02261ce4 *self)
{
    int a;
    short v1;
    short v2;
    v1 = 0x4a30;
    a = 0;
    func_020154b4(self, &v1, 0, 5, a);
    v2 = 0x4a30;
    func_0209a000(&v2, 0);
    self->unk_CC = -1;
    self->unk_D0 = 0x38;
}

void func_ov050_02261cd8(struct UnkStruct_02261cd8 *p)
{
    p->unk_CC = -2;
}

void func_ov050_02261cb4(int r0)
{
    int r4 = r0;
    func_020157c8(r4, 0x1d, 0);
    func_02015828(r4, 2);
    func_ov050_02263b38(r4, 0);
}

void func_ov050_02261ca0(struct UnkStruct_02261ca0 *p)
{
    func_0201b3a4(p->unk_B4, p->unk_C4);
}

void func_ov050_02261c7c(void *p)
{
    func_020157c8((int) p, 0x3e, 0);
    func_02015828((int) p, 2);
    func_ov050_02263b38((int) p, 1);
}

void func_ov050_02261bb8(UnkStruct_02261bb8 *self)
{
    u16 tmp;
    u16 *p;
    int r;
    unsigned int ok;
    unsigned int in1;
    unsigned int in2;
    u16 v;

    p = (u16 *) (self->unk_B4 + 0x732);
    if (func_0204bcdc(p) != 0) {
        tmp = 0xfff1;
        r = func_0204bc64(p);
        ok = (r == func_0204bc64(&tmp)) ? 1 : 0;
    } else {
        ok = (*p == 0xfff1) ? 1 : 0;
    }
    if (ok == 0) {
        in1 = 0;
        if (*(u16 *) (self->unk_B4 + 0x732) >= 0x1521 && *(u16 *) (self->unk_B4 + 0x732) <= 0x1530) {
            in1 = 1;
        }
        if (in1 != 0) {
            self->unk_D0 = 0x2f;
            in2 = 0;
            v = *(u16 *) (self->unk_B4 + 0x732);
            if (v >= 0x1521 && v <= 0x1530) {
                in2 = 1;
            }
            func_02060de4(((int *) data_021ebcd4), (u8) (in2 != 0 ? v - 0x1521 : -1));
        } else {
            self->unk_D0 = 0x23;
        }
    }
}

void func_ov050_02261918(UnkStruct_02261918_2 *self)
{
    u16 tmp;
    u16 *p;
    int g;
    int t;
    int ok;
    int flag;

    p = &self->unk_B4->unk_732;
    if (func_0204bcdc(p) != 0) {
        tmp = 0xfff1;
        t = func_0204bc64(p);
        if (t == func_0204bc64(&tmp)) {
            ok = 1;
        } else {
            ok = 0;
        }
    } else {
        ok = (*p == 0xfff1) ? 1 : 0;
    }
    if (ok != 0) {
        return;
    }

    g = func_020984e8();
    do {
        flag = 0;
        if (self->unk_B4->unk_732 >= 0x1369 && self->unk_B4->unk_732 <= 0x1369) {
            flag = 1;
        }
        if (flag != 0 && func_02099020(g, 0x29) == 0) {
            self->unk_D0 = 0x24;
            func_02098ff8(g, 0x29);
            break;
        }
        flag = 0;
        if (self->unk_B4->unk_732 >= 0x1376 && self->unk_B4->unk_732 <= 0x1376) {
            flag = 1;
        }
        if (flag != 0 && func_02099020(g, 0x2a) == 0) {
            self->unk_D0 = 0x25;
            func_02098ff8(g, 0x2a);
            break;
        }
        flag = 0;
        if (self->unk_B4->unk_732 >= 0x1374 && self->unk_B4->unk_732 <= 0x1374) {
            flag = 1;
        }
        if (flag != 0 && func_02099020(g, 0x2b) == 0) {
            self->unk_D0 = 0x26;
            func_02098ff8(g, 0x2b);
            break;
        }
        flag = 0;
        if (self->unk_B4->unk_732 >= 0x136b && self->unk_B4->unk_732 <= 0x1372) {
            flag = 1;
        }
        if (flag != 0 && func_02099020(g, 0x2c) == 0) {
            self->unk_D0 = 0x27;
            func_02098ff8(g, 0x2c);
            break;
        }
        flag = 0;
        if (self->unk_B4->unk_732 >= 0x1378 && self->unk_B4->unk_732 <= 0x1378) {
            flag = 1;
        }
        if (flag != 0 && func_02099020(g, 0x2d) == 0) {
            self->unk_D0 = 0x28;
            func_02098ff8(g, 0x2d);
            break;
        }
        flag = 0;
        if (self->unk_B4->unk_732 >= 0x137a && self->unk_B4->unk_732 <= 0x137a) {
            flag = 1;
        }
        if (flag != 0 && func_02099020(g, 0x2e) == 0) {
            self->unk_D0 = 0x29;
            func_02098ff8(g, 0x2e);
            break;
        }
        flag = 0;
        if (self->unk_B4->unk_732 >= 0x151f && self->unk_B4->unk_732 <= 0x151f) {
            flag = 1;
        }
        if (flag != 0 && func_02099020(g, 0x2f) == 0) {
            self->unk_D0 = 0x39;
            func_02098ff8(g, 0x2f);
            break;
        }
        flag = 0;
        if (self->unk_B4->unk_732 >= 0x156c && self->unk_B4->unk_732 <= 0x156c) {
            flag = 1;
        }
        if (flag != 0 && func_02099020(g, 0x37) == 0) {
            self->unk_D0 = 0x10;
            func_02098ff8(g, 0x37);
            break;
        }
    } while (0);

    if (self->unk_D0 == 0xff && func_0202e9fc() != 0 && func_ov050_02260510(self->unk_B4) != 0 &&
        func_02099020(g, 0x38) == 0) {
        self->unk_D0 = 0x30;
        func_02098ff8(g, 0x38);
    } else {
        func_0206844c(self->unk_40, data_021f43e8, 0);
    }
}

void func_ov050_02261908(void)
{
    func_02060cf4((void *) data_021ebcd4);
}

void func_ov050_022618d0(struct FuncOv050Obj *obj, int index, unsigned int offset)
{
    unsigned char value;
    unsigned char local;
    value = *(data_ov050_022650b4 + (index << 2) + offset);
    local = value;
    func_020683e4(obj->unk_40, 2, &local, data_ov050_02265e9c);
    func_02060c80(data_021ebcd4, value);
}
