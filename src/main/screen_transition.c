/* screen_transition: 23 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020421d0 @ 0x020421d0, 0x30 bytes, Thumb
 * func_020421cc @ 0x020421cc, 0x2 bytes, Thumb
 * func_020421a8 @ 0x020421a8, 0x24 bytes, Thumb
 * func_02042198 @ 0x02042198, 0x10 bytes, Thumb
 * func_02042154 @ 0x02042154, 0x44 bytes, Thumb
 * func_02042120 @ 0x02042120, 0x34 bytes, Thumb
 * func_02041fe0 @ 0x02041fe0, 0x140 bytes, Thumb
 * func_02041f6c @ 0x02041f6c, 0x74 bytes, Thumb
 * func_02041f20 @ 0x02041f20, 0x4c bytes, Thumb
 * func_02041e48 @ 0x02041e48, 0xd8 bytes, Thumb
 * func_02041e0c @ 0x02041e0c, 0x3c bytes, Thumb
 * func_02041e00 @ 0x02041e00, 0xc bytes, Thumb
 * func_02041dfc @ 0x02041dfc, 0x2 bytes, Thumb
 * func_02041df8 @ 0x02041df8, 0x2 bytes, Thumb
 * func_02041df4 @ 0x02041df4, 0x2 bytes, Thumb
 * func_02041dc4 @ 0x02041dc4, 0x30 bytes, Thumb
 * func_02041d14 @ 0x02041d14, 0xb0 bytes, Thumb
 * func_02041c88 @ 0x02041c88, 0x8c bytes, Thumb
 * func_02041c28 @ 0x02041c28, 0x60 bytes, Thumb
 * func_02041bb8 @ 0x02041bb8, 0x70 bytes, Thumb
 * func_02041b90 @ 0x02041b90, 0x28 bytes, Thumb
 * func_02041b74 @ 0x02041b74, 0x1c bytes, Thumb
 * func_02041a9c @ 0x02041a9c, 0xd8 bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned char unk_00;
    unsigned char unk_01;
    unsigned char pad_02[10];
    int unk_0C;
} Struct020421d0;

typedef struct {
    unsigned short unk_00;
    unsigned short unk_02;
    unsigned short unk_04;
    unsigned short vcount;
    unsigned char pad_08[0x38];
    unsigned short win0h;
    unsigned char pad_42[0x1040 - 0x42];
    unsigned short subWin0h;
} IO;

struct UnkStruct_02041fe0 {
    int pad_00;
    unsigned int unk_04;
};

struct g21c75b8_type {
    unsigned char pad_00[4];
    unsigned int unk_04;
};

typedef struct {
    u8 unk_00;
    u8 unk_01;
    u8 pad[2];
    u32 unk_04;
    u32 unk_08;
} UnkStruct_02041d14;

typedef void (*Fn)(void);

typedef struct {
    Fn fn;
    char pad[12];
} UnkStruct_02041d14_2;

typedef struct {
    u8 unk_00;
    u8 unk_01;
    u8 pad[2];
    u32 unk_04;
    u32 unk_08;
} UnkStruct_02041c88;

typedef struct {
    Fn fn;
    char pad[12];
} UnkStruct_02041c88_2;

struct GlobalData {
    unsigned char unk_00;
    unsigned char unk_01;
    unsigned char pad[6];
    int n;
};

typedef void (*Handler)(void);

struct HandlerEntry {
    Handler handler;
    char pad[12];
};

struct FuncTableEntry {
    void (*func)(void);
    char pad[12];
};

struct GlobalVars {
    unsigned char state;
    unsigned char index;
    char pad[6];
    unsigned int unk_08;
};

extern void func_02001aac(int arg);
extern unsigned char data_021c75b8[];
extern void func_0203de6c(int screen);
extern void func_02001bb4(int);
extern void func_02001b7c(int);
extern void func_02001da0(int);
extern void func_02001d74(int, int);
extern void func_02001d1c(int);
extern void func_02001d00(int);
extern void func_02001cc4(int, int, int, int);
extern void func_02001c7c(int, int, int, int);
extern void func_02001b44(int);
extern void func_02001b0c(int);
extern int G2_GetBG2ScrPtr(void);
extern int G2_GetBG2CharPtr(void);
extern int G2S_GetBG2ScrPtr(void);
extern int G2S_GetBG2CharPtr(void);
extern void MIi_CpuClear16(unsigned short, int, int);
extern unsigned int data_021c75b4;
extern unsigned char data_021c75cc;
extern int func_0205c024(void *, void (*)(void), void (*)(void), int);
extern unsigned char data_021c75ac;
extern void func_02001ba4(int);
extern void func_02001b6c(int);
extern int func_0205bfdc(int *);
extern void func_02001b34(int);
extern void func_02001afc(int);
extern void func_0203de68(int screen);
extern unsigned short data_021c76a8[96];
extern unsigned short data_021c75e8[96];
extern int FX_Sqrt(int value);
extern u8 data_021c75b0;
extern UnkStruct_02041d14_2 data_020ca518[];
extern UnkStruct_02041d14_2 data_020ca514[];
extern char *data_021c526c;
extern int FX_Div(int a, int b);
extern void func_02035e90(void *p);
extern void func_0208f97c(int a);
extern void func_0200468c(void);
extern void func_02035dcc(void *p);
extern void func_0208f95c(int a);
extern int func_02038a44(void);
extern int func_020e88dc(void *, int, int);
extern int data_021c75bc;
extern struct HandlerEntry data_020ca51c[];
extern struct FuncTableEntry data_020ca520[];
extern void func_02001b54(int);
extern void func_02001b1c(int);

void func_02041b90(void);
void func_02041b74(void);
void func_02041a9c(void);

void func_020421d0(void)
{
    Struct020421d0 *p = ((Struct020421d0 *) data_021c75b8);
    if (p->unk_00 == 3) {
        p->unk_0C = 0;
    } else {
        if (p->unk_01 == 0) {
            p->unk_0C = -16;
        } else {
            p->unk_0C = 0x10;
        }
    }
    func_02001aac(p->unk_0C);
}

void func_020421cc(void) {}

void func_020421a8(void)
{
    unsigned char b;
    int i;

    b = data_021c75b8[1];
    if (b == 0) {
        i = *(int *) (data_021c75b8 + 4);
        i = i << 4;
        i = -i;
        i = i >> 12;
        *(int *) (data_021c75b8 + 12) = i;
    } else {
        i = *(int *) (data_021c75b8 + 4);
        i = i << 4;
        i = i >> 12;
        *(int *) (data_021c75b8 + 12) = i;
    }
}

void func_02042198(void)
{
    func_02001aac((*(struct { char pad[12]; int field; } *) data_021c75b8).field);
}

void func_02042154(void)
{
    volatile IO *io = (volatile IO *) 0x04000000;
    int y;
    unsigned short v;
    y = io->vcount;
    if (y >= 0xc0) {
        return;
    }
    if (y >= 0x60) {
        y = 0xbf - y;
    }
    v = (*(unsigned short * *) &data_021c75b4)[y];
    if ((*(volatile unsigned short *) 0x04000004 & 2) != 0) {
        io->win0h = v;
        io->subWin0h = v;
    }
}

void func_02042120(void)
{
    *((volatile unsigned short *) 0x04000040) = *(*(volatile unsigned short * *) &data_021c75b4);
    *((volatile unsigned short *) 0x04001040) = *(*(volatile unsigned short * *) &data_021c75b4);
    *((volatile unsigned short *) 0x04000044) = 0xC0;
    *((volatile unsigned short *) 0x04001044) = 0xC0;
}

void func_02041fe0(void)
{
    volatile unsigned short arr[6];
    volatile unsigned short *reg;
    int ret;

    func_0203de6c(0);
    func_02001bb4(1);
    func_02001b7c(1);
    func_02001da0(0x1b);
    func_02001d74(0x1b, 1);
    func_02001d1c(4);
    func_02001d00(4);

    if ((*(struct UnkStruct_02041fe0 *) data_021c75b8).unk_04 == 0) {
        func_02001cc4(0, 0, 0xff, 0xc0);
        func_02001c7c(0, 0, 0xff, 0xc0);
    } else {
        func_02001cc4(0, 0, 0, 0);
        func_02001c7c(0, 0, 0, 0);
    }

    reg = (volatile unsigned short *) 0x0400000c;
    *reg &= ~3;
    *reg = (*reg & 0x43) | 0x600;

    ret = G2_GetBG2ScrPtr();
    arr[0] = 0;
    MIi_CpuClear16(arr[0], ret, 0x800);

    ret = G2_GetBG2CharPtr();
    arr[1] = 0x1111;
    MIi_CpuClear16(arr[1], ret, 0x20);

    arr[2] = 0x8000;
    MIi_CpuClear16(arr[2], 0x05000000, 4);
    func_02001b44(4);

    reg = (volatile unsigned short *) 0x0400100c;
    *reg &= ~3;
    *reg = (*reg & 0x43) | 0xe04;

    ret = G2S_GetBG2ScrPtr();
    arr[3] = 0;
    MIi_CpuClear16(arr[3], ret, 0x800);

    ret = G2S_GetBG2CharPtr();
    arr[4] = 0x1111;
    MIi_CpuClear16(arr[4], ret, 0x20);

    arr[5] = 0x8000;
    MIi_CpuClear16(arr[5], 0x05000400, 4);
    func_02001b0c(4);
}

void func_02041f6c(void)
{
    volatile unsigned short local = 0;
    MIi_CpuClear16(local, (int) ((void *) ((unsigned char *) data_021c75e8)), 0x180);
    data_021c75b4 = (unsigned int) ((unsigned char *) data_021c75e8);
    func_02041fe0();
    if (func_0205c024((void *) &data_021c75cc, func_02042154, func_02042120, 0) != 0) {
        data_021c75ac |= 1;
    }
    if ((*(struct g21c75b8_type *) data_021c75b8).unk_04 == 0x1000) {
        func_02001aac(0);
    }
}

void func_02041f20(void)
{
    func_02001ba4(1);
    func_02001b6c(1);
    if (data_021c75ac & 1) {
        func_0205bfdc(((int *) &data_021c75cc));
        data_021c75ac &= ~1;
    }
    func_02001b34(4);
    func_02001afc(4);
    func_0203de68(0);
}

void func_02041e48(void)
{
    volatile unsigned short value[2];
    unsigned short *p;
    struct UnkStruct_02041e48 *p_data = ((struct UnkStruct_02041e48 { int a; int b; } *) data_021c75b8);
    int i, r7, r6;

    if (data_021c75ac & 2) {
        p = data_021c75e8;
    } else {
        p = data_021c76a8;
    }

    {
        int b = p_data->b;
        if (b == 0) {
            value[0] = 0xff;
            MIi_CpuClear16(value[0], (int) p, 0xc0);
            return;
        } else if (b == 0x1000) {
            value[1] = 0x8080;
            MIi_CpuClear16(value[1], (int) data_021c75e8, 0x180);
            return;
        } else {
            r7 = (0x1000 - b) * 0xa0 >> 12;
            r6 = (r7 * r7) << 12;
            for (i = 0; i < 0x60; i++) {
                int delta = 0x60 - i;
                if (delta > r7) {
                    *p = 0x8080;
                } else {
                    int param = r6 - ((delta * delta) << 12);
                    int result = FX_Sqrt(param);
                    if (result < 0x80000) {
                        int t = (result >> 12);
                        t = 0x80 - t;
                        t &= 0xffff;
                        *p = (unsigned short) (((t << 8) & 0xff00) | ((0x100 - t) & 0xff));
                    } else {
                        *p = 0xff;
                    }
                }
                p++;
            }
        }
    }
}

void func_02041e0c(void)
{
    unsigned char tmp;

    tmp = data_021c75ac;
    if (tmp & 2) {
        data_021c75b4 = (unsigned int) ((unsigned char *) data_021c75e8);
        tmp &= ~2;
        data_021c75ac = tmp;
    } else {
        data_021c75b4 = (unsigned int) ((unsigned char *) data_021c76a8);
        tmp |= 2;
        data_021c75ac = tmp;
    }
}

void func_02041e00(void)
{
    func_02001aac(0);
}

void func_02041dfc(void) {}

void func_02041df8(void) {}

void func_02041df4(void) {}

void func_02041dc4(void)
{
    (*(struct { char f0; char f1; int f4; int f8; int fC; } *) data_021c75b8).f0 = 0;
    (*(struct { char f0; char f1; int f4; int f8; int fC; } *) data_021c75b8).f1 = 0;
    (*(struct { char f0; char f1; int f4; int f8; int fC; } *) data_021c75b8).fC = -16;
    (*(struct { char f0; char f1; int f4; int f8; int fC; } *) data_021c75b8).f4 = 0x1000;
    (*(struct { char f0; char f1; int f4; int f8; int fC; } *) data_021c75b8).f8 = 0;
    (*(int *) &data_021c75b4) = 0;
    (*(char *) &data_021c75ac) = 0;
}

int func_02041d14(int a, int b)
{
    unsigned int ok;
    Fn fn;
    int old;

    old = (*(UnkStruct_02041d14 *) data_021c75b8).unk_01;
    if ((*(UnkStruct_02041d14 *) data_021c75b8).unk_00 == 2) {
        ok = 1;
    } else {
        ok = 0;
    }
    if (ok == 0 && data_021c75b0 == 0) {
        return 0;
    }
    (*(UnkStruct_02041d14 *) data_021c75b8).unk_00 = 3;
    data_021c75b0 = 0;
    fn = data_020ca518[old].fn;
    if (fn != 0) {
        fn();
    }
    (*(UnkStruct_02041d14 *) data_021c75b8).unk_01 = (u8) a;
    (*(UnkStruct_02041d14 *) data_021c75b8).unk_04 = 0;
    fn = data_020ca514[a].fn;
    if (fn != 0) {
        fn();
        func_02035e90(data_021c526c + 0x2d0);
        func_0208f97c(a);
        if (a == 2) {
            func_0200468c();
        }
    }
    if (b == 0 || a == 3) {
        (*(UnkStruct_02041d14 *) data_021c75b8).unk_08 = 0x1000;
    } else {
        (*(UnkStruct_02041d14 *) data_021c75b8).unk_08 = FX_Div(0x1000, b << 12);
    }
    return 1;
}

int func_02041c88(int a, int b, int c)
{
    unsigned int ok;
    Fn fn;

    if ((*(UnkStruct_02041c88 *) data_021c75b8).unk_00 == 0) {
        ok = 1;
    } else {
        ok = 0;
    }
    if (ok == 0) {
        return 0;
    }
    func_02041b74();
    (*(UnkStruct_02041c88 *) data_021c75b8).unk_00 = 1;
    (*(UnkStruct_02041c88 *) data_021c75b8).unk_01 = (u8) a;
    (*(UnkStruct_02041c88 *) data_021c75b8).unk_04 = 0x1000;
    fn = ((UnkStruct_02041c88_2 *) data_020ca514)[a].fn;
    if (fn != 0) {
        fn();
    }
    if (b == 0 || a == 3) {
        (*(UnkStruct_02041c88 *) data_021c75b8).unk_08 = 0xfffff000;
    } else {
        (*(UnkStruct_02041c88 *) data_021c75b8).unk_08 = FX_Div(0xfffff000, b << 12);
    }
    if (c == 0) {
        func_02035dcc(data_021c526c + 0x2d0);
        func_0208f95c(a);
    }
    return 1;
}

void func_02041c28(void)
{
    unsigned char c1;
    unsigned char c0;
    int n;
    int flag;

    if (func_02038a44() != 0) {
        return;
    }
    c1 = (*(struct GlobalData *) data_021c75b8).unk_01;
    c0 = (*(struct GlobalData *) data_021c75b8).unk_00;
    if (c0 == 0 || c0 == 2) {
        return;
    }
    n = (*(struct GlobalData *) data_021c75b8).n;
    if (n != 0) {
        if (n >= 0) {
            flag = 0x1000;
        } else {
            flag = 0;
        }
        if (n < 0) {
            n = -n;
        }
        if (func_020e88dc(&data_021c75bc, flag, n) != 0) {
            (*(struct GlobalData *) data_021c75b8).n = 0;
        }
    }
    if (data_020ca51c[c1].handler != 0) {
        data_020ca51c[c1].handler();
    }
}

void func_02041bb8(void)
{
    unsigned char index;
    unsigned char state;

    if (func_02038a44() != 0) {
        return;
    }

    index = (*(struct GlobalVars *) data_021c75b8).index;
    state = (*(struct GlobalVars *) data_021c75b8).state;

    if (state == 2 || state == 0) {
        return;
    }

    if (data_020ca520[index].func != 0) {
        data_020ca520[index].func();
    }

    if ((*(struct GlobalVars *) data_021c75b8).state == 1) {
        if ((*(struct GlobalVars *) data_021c75b8).unk_08 != 0) {
            return;
        }
        (*(struct GlobalVars *) data_021c75b8).state = 2;
        if (((struct FuncTableEntry *) data_020ca518)[index].func != 0) {
            ((struct FuncTableEntry *) data_020ca518)[index].func();
        }
        return;
    } else if ((*(struct GlobalVars *) data_021c75b8).state == 3) {
        if ((*(struct GlobalVars *) data_021c75b8).unk_08 != 0) {
            return;
        }
        (*(struct GlobalVars *) data_021c75b8).state = 0;
        if (((struct FuncTableEntry *) data_020ca518)[index].func != 0) {
            ((struct FuncTableEntry *) data_020ca518)[index].func();
        }
        func_02041b90();
        return;
    } else {
        return;
    }
}

void func_02041b90(void)
{
    func_0203de6c(0);
    func_02001b54(0x10);
    func_02001b1c(0);
    func_02041a9c();
    func_02001aac(~0xf);
}

void func_02041b74(void)
{
    func_02001b34(4);
    func_02001afc(4);
    func_0203de68(0);
}

void func_02041a9c(void)
{
    volatile u16 arr[6];
    u32 v;

    *(volatile u16 *) 0x0400000c &= ~3;
    *(volatile u16 *) 0x0400000c = (*(volatile u16 *) 0x0400000c & 0x43) | 0x600;

    v = (u32) G2_GetBG2ScrPtr();
    arr[0] = 0;
    MIi_CpuClear16((u16) arr[0], v, 0x800);

    v = (u32) G2_GetBG2CharPtr();
    arr[1] = 0x1111;
    MIi_CpuClear16((u16) arr[1], v, 0x20);

    arr[2] = 0x8000;
    MIi_CpuClear16((u16) arr[2], 0x05000000, 4);

    func_02001b44(4);

    *(volatile u16 *) 0x0400100c &= ~3;
    *(volatile u16 *) 0x0400100c = (*(volatile u16 *) 0x0400100c & 0x43) | 0xe04;

    v = (u32) G2S_GetBG2ScrPtr();
    arr[3] = 0;
    MIi_CpuClear16((u16) arr[3], v, 0x800);

    v = (u32) G2S_GetBG2CharPtr();
    arr[4] = 0x1111;
    MIi_CpuClear16((u16) arr[4], v, 0x20);

    arr[5] = 0x8000;
    MIi_CpuClear16((u16) arr[5], 0x05000400, 4);

    func_02001b0c(4);
}
