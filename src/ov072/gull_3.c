/* gull_3: 5 functions, module ov072
 * mwccarm 1.2/base -O4,s
 * func_ov072_02279618 @ 0x02279618, 0xe bytes, Thumb
 * func_ov072_022795ac @ 0x022795ac, 0x6c bytes, Thumb
 * func_ov072_022795a8 @ 0x022795a8, 0x4 bytes, Thumb
 * func_ov072_02279518 @ 0x02279518, 0x90 bytes, Thumb
 * func_ov072_02279424 @ 0x02279424, 0xf4 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0x3b0];
    int unk_3B0;
    char pad_3B4[0x564 - 0x3b4];
    int unk_564;
    char pad_568[0x718 - 0x568];
    unsigned char unk_718;
    char pad_719[3];
    int unk_71C;
} UnkStruct_02279518;

typedef struct {
    char pad_00[0x564];
    char unk_564;
    char pad_565[0x718 - 0x565];
    u8 unk_718;
    char pad_719[3];
    int unk_71C;
    int unk_720;
} UnkStruct_02279424;

extern void func_0201ad18(void *a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8);
extern int func_02019c20(void *a1, int a2, int a3, int a4, int a5, int a6);
extern void func_0201b38c(void *a1, int a2);
extern int data_020c814c;
extern unsigned short data_020c80f8;
extern unsigned char data_021fbee8[];
extern int func_02019d0c(void *, int, int, int, int, int, int, int, int, int, int);
extern int func_020644cc(int);
extern int func_02019c90(void *p, int a, int b, int c);

int func_ov072_02279618(int unused, int *p)
{
    if (*p != 0) {
        (*p)--;
    }
    return *p;
}

int func_ov072_022795ac(void *param)
{
    func_0201ad18((char *) param + 0x3b0, 0, 0, 0, (unsigned int) data_021fbee8, 4, data_020c814c, 1);
    func_02019c20((char *) param + 0x564, 1, 0xef, 1, data_020c80f8, 0);
    func_0201b38c((char *) param + 0x2a0, 0xef);
    return 1;
}

int func_ov072_022795a8(void)
{
    return 1;
}

int func_ov072_02279518(UnkStruct_02279518 *obj)
{
    func_02019d0c(&obj->unk_564, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    func_0201ad18(&obj->unk_3B0, 1, 0, 0, (int) (((int *) data_021fbee8)), 4, data_020c814c, 1);
    if (obj->unk_718 != 0) {
        obj->unk_71C = 0x190;
        obj->unk_71C = obj->unk_71C + func_020644cc(0x258);
    }
    return 1;
}

int func_ov072_02279424(UnkStruct_02279424 *self)
{
    int r;

    if (self->unk_718 != 0) {
        if (func_ov072_02279618((int) self, (int *) (&self->unk_720)) == 2) {
            func_02019c90(&self->unk_564, 1, 0, data_020c80f8);
            return 1;
        }
        if (self->unk_720 == 1) {
            func_02019d0c(&self->unk_564, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
            return 1;
        }
        if (func_ov072_02279618((int) self, (int *) (&self->unk_71C)) == 0) {
            r = func_020644cc(3);
            switch (r) {
                case 0:
                    func_02019c90(&self->unk_564, 1, 0xc, data_020c80f8);
                    break;
                case 1:
                    func_02019c90(&self->unk_564, 1, 0xd, data_020c80f8);
                    break;
                case 2:
                    func_02019c90(&self->unk_564, 1, 0xe, data_020c80f8);
                    break;
            }
            self->unk_71C = 0x190;
            self->unk_71C = self->unk_71C + func_020644cc(0x258);
            self->unk_720 = 0x7a;
        }
    }
    return 1;
}
