/* scene_command_8: 8 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020157c8 @ 0x020157c8, 0xc bytes, Thumb
 * func_020157b0 @ 0x020157b0, 0x18 bytes, Thumb
 * func_020157a4 @ 0x020157a4, 0xa bytes, Thumb
 * func_0201579c @ 0x0201579c, 0x8 bytes, Thumb
 * func_02015774 @ 0x02015774, 0x28 bytes, Thumb
 * func_02015760 @ 0x02015760, 0x12 bytes, Thumb
 * func_02015688 @ 0x02015688, 0xd6 bytes, Thumb
 * func_02015654 @ 0x02015654, 0x32 bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned char pad_00[0x6c];
    int unk_6C;
    int unk_70;
    unsigned char pad_74[0x14];
    unsigned char unk_88;
} UnkStruct_020157a4;

typedef struct {
    unsigned char pad_00[0x86];
    unsigned char unk_86;
    unsigned char pad_87;
    unsigned char unk_88;
    unsigned char pad_89[0x13];
    unsigned int unk_9C;
    unsigned int unk_A0;
} UnkStruct_02015774;

typedef struct {
    char pad_00[0x14];
    int unk_14;
} OtherStruct;

typedef struct {
    char pad_00[0x40];
    OtherStruct *unk_40;
    char pad_44[0xAC - 0x44];
    unsigned char unk_AC;
} UnkStruct_02015760;

// Both guards nest into one if, sharing the return 0 with the switch fallthrough.

typedef struct UnkStruct_02015688 {
    char pad_00[4];
    int unk_04;
    int unk_08;
} UnkStruct_02015688;

typedef struct UnkStruct_02015688_2 {
    char pad_00[0x40];
    UnkStruct_02015688 *unk_40;
    char pad_44[0x24];
    u32 unk_68;
    int unk_6C;
    int unk_70;
    int unk_74;
    int (*unk_78)(u16 *, int);
    u16 unk_7C;
    char pad_7E[6];
    u8 unk_84;
    char pad_85[1];
    u8 unk_86;
    u8 unk_87;
    u8 unk_88;
    char pad_89[0x13];
    int unk_9C;
    int unk_A0;
    char pad_A4[8];
    u8 unk_AC;
} UnkStruct_02015688_2;

struct UnkStruct_02015654 {
    char pad_00[0x40];
    int *ptr;
    char pad_44[0x44];
    unsigned char unk_88;
    char pad_89[0x23];
    unsigned char unk_AC;
};

extern u16 func_0206f9d8(int (*)(u16 *, int));
extern int func_0206fa28(int, u8);
extern int func_0206f99c(void);
extern int func_0206fbf8(u8);
extern int func_0206fbd8(u8, u8);
extern int func_0206f7dc(int, int);
extern int func_0206ffe8(int);
extern int func_0206f640(u8, int, int);
extern int func_0206fbc0(void);

void func_020157c8(char *param0, char param1, char param2)
{
    char *r3;
    char *r0;

    r3 = param0 + 0x86;
    *r3 = param1;
    r0 = param0 + 0x88;
    *r0 = param2;
}

void func_020157b0(unsigned char *arg0, unsigned char arg1, unsigned char arg2, unsigned char arg3)
{
    arg0[0x86] = arg1;
    arg0[0x87] = arg2;
    arg0[0x88] = arg3;
}

void func_020157a4(UnkStruct_020157a4 *p, int a, int b, int c)
{
    p->unk_6C = a;
    p->unk_70 = b;
    p->unk_88 = (unsigned char) c;
}

void func_0201579c(int *p0, int p1, int p2)
{
    p0[29] = p1;
    *(unsigned char *) ((char *) (((int) ((int) p0) + (136))) + (0)) = p2;
}

void func_02015774(UnkStruct_02015774 *s, unsigned char a, unsigned int b, unsigned int c, unsigned char d)
{
    s->unk_86 = a;
    s->unk_9C = b;
    s->unk_A0 = c;
    s->unk_88 = d;
}

int func_02015760(UnkStruct_02015760 *param)
{
    OtherStruct *ptr;
    ptr = param->unk_40;
    if (ptr) {
        ptr->unk_14 = 1;
        param->unk_AC = 1;
    }
    return 0;
}

int func_02015688(UnkStruct_02015688_2 *o)
{
    UnkStruct_02015688 *p;
    int r;
    int v;

    p = o->unk_40;
    if (p != 0 && p->unk_04 == 5) {
        r = 0;
        switch (o->unk_68) {
            case 0:
                v = o->unk_7C;
                if (o->unk_78 != 0) {
                    v = func_0206f9d8(o->unk_78);
                }
                r = func_0206fa28(v, o->unk_84);
                break;
            case 1:
                o->unk_88 = 1;
                r = func_0206f99c();
                break;
            case 2:
                r = func_0206fbf8(o->unk_86);
                break;
            case 3:
                r = func_0206fbd8(o->unk_86, o->unk_87);
                break;
            case 4:
                r = func_0206f7dc(o->unk_6C, o->unk_70);
                break;
            case 5:
                r = func_0206ffe8(o->unk_74);
                break;
            case 6:
                r = func_0206f640(o->unk_86, o->unk_9C, o->unk_A0);
                break;
            case 7:
                if (o->unk_88 != 1) {
                    p->unk_08 = 1;
                }
                o->unk_AC = 3;
                return 1;
        }
        if (r != 0) {
            o->unk_AC = 2;
        }
    }
    return 0;
}

int func_02015654(void *param)
{
    struct UnkStruct_02015654 *s = (struct UnkStruct_02015654 *) param;
    int ret = 0;
    if (func_0206fbc0() != 0) {
        if (s->unk_88 != 1) {
            *(int *) ((char *) s->ptr + 8) = 1;
        }
        s->unk_AC = 3;
        ret = 1;
    }
    return ret;
}
