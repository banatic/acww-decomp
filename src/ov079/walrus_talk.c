/* walrus_talk: 4 functions, module ov079
 * mwccarm 1.2/base -O4,s
 * func_ov079_02278c4c @ 0x02278c4c, 0x30 bytes, Thumb
 * func_ov079_02278c38 @ 0x02278c38, 0x14 bytes, Thumb
 * func_ov079_02278b2c @ 0x02278b2c, 0x10c bytes, Thumb
 * func_ov079_02278ac4 @ 0x02278ac4, 0x68 bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned int unk_00;
    unsigned char unk_04;
} UnkStruct_02278c4c;

struct UnkStruct_02278c38 {
    unsigned char pad_00[0x1e];
    unsigned char unk_1E;
};

typedef struct {
    char pad_00[0x1E];
    u8 unk_1E;
    char pad_1F[0x21];
    void *unk_40;
    char pad_44[0xc4 - 0x44];
    u16 unk_C4;
} UnkStruct_02278b2c;

typedef struct {
    char pad_00[0x1E];
    unsigned char unk_1E;
    char pad_1F[0x21];
    void *unk_40;
} UnkStruct_02278ac4;

extern unsigned char data_ov079_0227a1b0[];
extern int func_0202ea80(int a, int b);
extern int func_020644cc(int a);
extern int func_02014d04(void *);
extern int func_02015094(UnkStruct_02278b2c *p);
extern void func_02015de4(UnkStruct_02278b2c *p, u16 *q, int a, int b);
extern void func_0204093c(int a);
extern void func_020157c8(UnkStruct_02278b2c *p, int a, int b);
extern int func_02015828(UnkStruct_02278b2c *p, int a);
extern void func_ov079_02279518(UnkStruct_02278b2c *p, int a);
extern int func_0209a000(u16 *p, int a);
extern int func_020154b4(UnkStruct_02278b2c *p, u16 *q, int a, int b, int c);
extern int func_02014f60(UnkStruct_02278b2c *p);
extern void func_0206844c(void *a, char *b, void *c);
extern int func_020160b4(void *arg);
extern int func_020ab504(int value);
extern void func_020157d4(void *obj, unsigned int address, unsigned char state, unsigned char flags);
extern int func_ov079_022794fc(int argument0, int argument1);

void func_ov079_02278c4c(int unused, UnkStruct_02278c4c *self)
{
    self->unk_00 = (unsigned int) data_ov079_0227a1b0;
    if (func_0202ea80(10, 0) == 0) {
        self->unk_04 = 0;
    } else {
        self->unk_04 = (unsigned char) (func_020644cc(3) + 6);
    }
}

void func_ov079_02278c38(struct UnkStruct_02278c38 *self)
{
    if (self->unk_1E == 0xf) {
        func_02014d04(self);
    }
}

void func_ov079_02278b2c(UnkStruct_02278b2c *arg)
{
    void *p = ((char *) data_ov079_0227a1b0);
    int r4 = 0xff;
    int cond;
    char local;

    switch (arg->unk_1E) {
        case 3:
            r4 = 0xf;
            break;
        case 2:
            func_02015094(arg);
            break;
        case 15:
            r4 = 4;
            cond = 0;
            if (arg->unk_C4 >= 0x153b && arg->unk_C4 <= 0x1541) {
                cond = 1;
            }
            if (cond != 0) {
                arg->unk_C4 = 0x13ac;
                if (func_020644cc(2) != 0) {
                    arg->unk_C4 = 0x3530;
                }
                r4 = 9;
                func_02015de4(arg, &arg->unk_C4, 0, 7);
            }
            func_0204093c(0x41);
            break;
        case 14:
            func_020157c8(arg, 10, 0);
            func_02015828(arg, 2);
            func_ov079_02279518(arg, 2);
            break;
        case 11:
            func_02014f60(arg);
            break;
        case 9:
            if (func_0209a000(&arg->unk_C4, 0) != 0) {
                func_020154b4(arg, &arg->unk_C4, 0, 5, 0);
            }
            r4 = 10;
            break;
        case 5:
        case 10:
        case 13:
            func_0202ea80(10, 1);
            break;
    }

    if (r4 != 0xff) {
        local = (char) r4;
        func_0206844c(arg->unk_40, &local, p);
    }
}

void func_ov079_02278ac4(UnkStruct_02278ac4 *arg)
{
    int result;
    void *p;
    int r4;
    unsigned char field;
    char local;

    result = func_020ab504(func_020160b4(arg));
    p = ((char *) data_ov079_0227a1b0);
    r4 = 0xFF;
    field = arg->unk_1E;

    switch (field) {
        case 0:
            if (result == 0) {
                func_020157d4(arg, (unsigned int) func_ov079_022794fc, 0xD, 1);
                func_02015828((UnkStruct_02278b2c *) arg, 0);
                func_ov079_02279518((UnkStruct_02278b2c *) arg, 0);
            }
            break;
        case 4:
            if (result == 0) {
                r4 = 0x0E;
            }
            break;
    }

    if (r4 != 0xFF) {
        local = (char) r4;
        func_0206844c(arg->unk_40, &local, p);
    }
}
