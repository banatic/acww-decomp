/* xct_exchange_talk_2: 3 functions, module ov055
 * mwccarm 1.2/base -O4,s
 * func_ov055_022609f4 @ 0x022609f4, 0x10 bytes, Thumb
 * func_ov055_02260930 @ 0x02260930, 0xc4 bytes, Thumb
 * func_ov055_0226090c @ 0x0226090c, 0x22 bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned int unk_00;
    unsigned char unk_04;
} Struct_ov055_022609f4;

typedef struct UnkStruct_02260930 {
    char pad_00[0x1e];
    u8 unk_1E;
    char pad_1F[0x40 - 0x1f];
    int unk_40;
    char pad_44[0xb0 - 0x44];
    char *unk_B0;
} UnkStruct_02260930;

typedef struct UnkStruct_0226090c {
    unsigned char pad_00[0x1e];
    unsigned char unk_1E;
    unsigned char pad_1F[0x40 - 0x1f];
    int unk_40;
} UnkStruct_0226090c;

extern unsigned int data_ov055_02260e60;
extern void func_02073090(void);
extern int func_020ead58(void);
extern void func_020ead88(void);
extern void func_020ead94(char *a, char *b, int n);
extern void func_02074af8(void);
extern void MI_CpuFill8(char *p, int v, int n);
extern void func_0206844c(int h, u8 *p, int k);
extern void func_02068440(int h);
extern void func_ov055_02260870(UnkStruct_02260930 *self, int a);
extern void func_ov055_0226068c(char *p);
extern void func_ov055_02260668(char *p);
extern int func_0206837c(int arg);
extern int func_020ab504(int arg);
extern void func_02074958(void);

int func_ov055_022609f4(int unused, Struct_ov055_022609f4 *out)
{
    out->unk_00 = data_ov055_02260e60;
    out->unk_04 = 0x38;
    return 0x38;
}

void func_ov055_02260930(UnkStruct_02260930 *self)
{
    u8 code;
    int h;
    char *p;

    h = self->unk_40;
    switch (self->unk_1E) {
        case 0x39:
            if (((void) (func_02073090()), func_020ead58()) == 0) {
                if (*(u8 *) (self->unk_B0 + 0x710) != 0) {
                    code = 0x36;
                    func_0206844c(h, &code, (*(int *) &data_ov055_02260e60));
                    break;
                }
                func_02074af8();
                MI_CpuFill8(self->unk_B0 + 0x116c, 0, 0xa58);
                p = self->unk_B0;
                func_02073090();
                func_020ead94(p + 0x714, p + 0x116c, 0xa58);
                ((void) (func_02073090()), func_020ead88());
            }
            ((void) (func_02073090()), func_020ead88());
            func_02068440(h);
            func_ov055_02260870(self, 1);
            break;
        case 0x3c:
            func_ov055_0226068c(self->unk_B0);
            break;
        case 0x3b:
            func_ov055_02260668(self->unk_B0);
            break;
    }
}

void func_ov055_0226090c(UnkStruct_0226090c *self)
{
    int ret = func_020ab504(func_0206837c(self->unk_40));
    if (self->unk_1E == 0x3a && ret == 1) {
        func_02074958();
    }
}
