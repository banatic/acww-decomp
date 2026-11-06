/* astro_3: 9 functions, module ov046
 * mwccarm 1.2/base -O4,s
 * func_ov046_02261960 @ 0x02261960, 0x6c bytes, Thumb
 * func_ov046_022618f0 @ 0x022618f0, 0x70 bytes, Thumb
 * func_ov046_022618b4 @ 0x022618b4, 0x3c bytes, Thumb
 * func_ov046_02261884 @ 0x02261884, 0x30 bytes, Thumb
 * func_ov046_02261820 @ 0x02261820, 0x64 bytes, Thumb
 * func_ov046_022617d4 @ 0x022617d4, 0x4c bytes, Thumb
 * func_ov046_02261750 @ 0x02261750, 0x84 bytes, Thumb
 * func_ov046_0226170c @ 0x0226170c, 0x44 bytes, Thumb
 * func_ov046_02261708 @ 0x02261708, 0x4 bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_02261820_3 {
    int unk_00;
    char pad1[0x18];
    unsigned short unk_1C;
    unsigned short unk_1E;
    unsigned char unk_20;
} UnkStruct_02261820_3;

typedef struct UnkStruct_02261820 {
    char pad_00[0x28];
    int unk_28;
    UnkStruct_02261820_3 sub;
} UnkStruct_02261820;

struct Src {
    int a;
    int b;
    int c;
};

struct UnkStruct_02261820_2 {
    unsigned char unk_00;
    char pad1[3];
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    unsigned char unk_18;
    char pad_19[3];
    unsigned short unk_1C;
    unsigned short unk_1E;
    char pad_20[4];
    unsigned short unk_24;
    unsigned short unk_26;
    char pad_28[2];
    unsigned char unk_2A;
    char pad_2B[0x31];
    int unk_5C;
    unsigned char unk_60;
    char pad_61[3];
    int unk_64;
};

typedef struct {
    unsigned char pad_00[0x8e];
    unsigned char unk_8E[0x478 - 0x8e];
    unsigned char unk_478[0x740 - 0x478];
    int unk_740;
} SelfType;

extern unsigned short data_020c80f8;
extern unsigned int data_020c814c;
extern int func_02019d0c(unsigned char *a, int b, int c, int d, int e, int f, int g, int h, int i, int j, int k);
extern void func_0201ad18(unsigned char *a, int b, int c, int d, void *e, int f, int g, int h);
extern int func_ov046_02260474(void *self);
extern void *data_020ccf94;
extern int func_02073d90(void *a);
extern short *func_0209d358(int a, int b);
extern int func_0209dcac(void);
extern int func_020e8840(void *p);
extern void func_ov046_022619cc(void *self, int a);
extern int func_02019e00(void *);
extern int func_02019de8(void *);
extern int func_02019c20(UnkStruct_02261820 *s, int x, int v, char c, unsigned short a, unsigned short b);
extern int func_020912d4(int a, void *b, void *c, int _x);
extern void func_02091278(int a, void *b, void *c, void *arg3);
extern int func_02016104(u8 *p);
extern int func_0201c314(u8 *self, int r);
extern void func_0209129c(int v);
extern int func_020147fc(u8 *p, int a, int b, int c);
extern u8 data_021fbee8[];
extern int func_02014868(void *p);
extern void func_ov046_02261268(void *p, int n);
extern int func_0203e020(void *p);

int func_ov046_02261960(unsigned char *self)
{
    func_02019d0c(self + 0x564, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    *(unsigned short *) (self + 0x738) = 0x78;
    func_0201ad18(self + 0x3b0, 1, 0, 0, ((int *) data_021fbee8), 4, data_020c814c, 1);
    return 1;
}

int func_ov046_022618f0(void *self)
{
    if (func_ov046_02260474(self)) {
        return 1;
    }

    if (func_02073d90(data_020ccf94) != 0 || func_0209d358(0, 0x4a)[0] != 0 || func_0209dcac() == 2 || func_0209dcac() == 3) {
        return 1;
    }

    if (func_020e8840((unsigned char *) self + 0x738) == 0) {
        *(unsigned short *) ((unsigned char *) self + 0x73c) = 0x18;
        func_ov046_022619cc(self, 2);
    }
    return 1;
}

int func_ov046_022618b4(void *self)
{
    int arg5;
    int arg6;
    int arg7;
    int arg8;
    int arg9;
    int arg10;
    int arg11;

    arg5 = 0;
    arg6 = 0;
    arg7 = *(signed short *) ((char *) self + 0x73a);
    arg8 = 0;
    arg9 = 0;
    arg10 = data_020c80f8;
    arg11 = 0;

    func_02019d0c((unsigned char *) ((char *) self + 0x564), 3, 1, 0, arg5, arg6, arg7, arg8, arg9, arg10, arg11);
    return 1;
}

int func_ov046_02261884(void *self)
{
    if (func_02019e00((char *) self + 0x564) == 3) {
        if (func_02019de8((char *) self + 0x564) != 0) {
            func_ov046_022619cc(self, 0);
        }
    }
    return 1;
}

int func_ov046_02261820(unsigned char *self)
{
    func_02019c20((UnkStruct_02261820 *) (self + 0x564), 1, 0xf0, 0, *(unsigned short *) (self + 0x73c), 0);
    func_0201ad18((unsigned char *) ((struct UnkStruct_02261820_2 *) (self + 0x3b0)), 0, 0, 0,
                  (void *) ((struct Src *) ((int *) data_021fbee8)), 4, data_020c814c, (unsigned char) 1);
    *(unsigned char *) (self + 0x73e) = 1;
    return 1;
}

int func_ov046_022617d4(SelfType *self)
{
    if (func_ov046_02260474((void *) self)) {
        return 1;
    }
    if (self->unk_740 == -1) {
        self->unk_740 = func_020912d4(0x3c, &self->unk_478, &self->unk_8E, 0);
    } else {
        func_02091278(self->unk_740, &self->unk_478, &self->unk_8E, (void *) 0);
    }
    return 1;
}

int func_ov046_02261750(u8 *self)
{
    int a;
    int r;

    r = func_02016104(self + 0x658);
    a = 0;
    if (r != 0) {
        a = func_0201c314(self, r);
    }
    if (*(int *) (self + 0x740) != -1) {
        func_0209129c(*(int *) (self + 0x740));
        *(int *) (self + 0x740) = -1;
    }
    func_020147fc(self + 0x618, 0, a, 0);
    func_0201ad18((unsigned char *) (self + 0x3b0), 1, 0, 0, data_021fbee8, 4, (*(int *) &data_020c814c), 1);
    return 1;
}

int func_ov046_0226170c(char *obj)
{
    if (func_02014868(obj + 0x618) == 0) {
        obj[0x73e] = 0;
        func_ov046_02261268(obj + 0x658, 5);
        func_0203e020(obj);
        func_ov046_022619cc(obj, 4);
    }
    return 1;
}

int func_ov046_02261708(void)
{
    return 1;
}
