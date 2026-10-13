/* func_ov071_02278ac4 @ 0x02278ac4, 0x188 bytes, Thumb, module ov071
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_020160b4(void *);
extern int func_020ab504(int);
extern int func_0201b43c(int, int);
extern void func_0202ea80(int, int);
extern void func_02040adc(int, int);
extern void func_020157d4(void *, void (*)(void), int, int);
extern void func_02015828(void *, int);
extern void func_ov071_02279128(void *, int);
extern void func_ov071_022790f0(void);
extern void MI_CpuFill8(void *, int, int);
extern void func_0206844c(int, u8 *, void *);
extern char data_ov071_0227a180;
extern u8 data_021dc7a8[];

typedef struct {
    char pad_00[0x1e];
    u8 unk_1E;
    char pad_1F[0x21];
    int unk_40;
    char pad_44[0x70];
    int unk_B4;
    u8 unk_B8;
} UnkStruct_02278ac4;

void func_ov071_02278ac4(UnkStruct_02278ac4 *p)
{
    u8 m;
    int r;
    void *dp;
    int code;
    u8 *q;
    int v;

    r = func_020ab504(func_020160b4(p));
    dp = &data_ov071_0227a180;
    code = 0xff;
    q = data_021dc7a8;
    v = p->unk_1E;
    switch (v) {
        case 0x28:
        case 0x29:
        case 0x2a:
        case 0x2b:
        case 0x2c:
            switch (r) {
                case 0:
                    code = 4;
                    break;
                case 1:
                    code = 2;
                    break;
            }
            break;
        case 8:
            code = (u8) (v + 1);
            q[0x17228] = (u8) (r + 1);
            break;
        case 0xc:
            switch (r) {
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                    code = 0xd;
                    MI_CpuFill8((void *) (p->unk_B4 + 0x724), 0, 5);
                    p->unk_B8 = 0;
                    if (r == 4) {
                        func_02040adc(0, 1);
                    } else {
                        func_02040adc(0, 0);
                    }
                    break;
            }
            break;
        case 0x15:
        case 0x17:
            if (r == 0) {
                func_0202ea80(0x28, 1);
                if (func_0201b43c(p->unk_B4, 0xbb8) != 0) {
                    code = 0x18;
                } else {
                    code = 0x16;
                }
            }
            break;
        case 0x1d:
        case 0x27:
            if (r == 0) {
                func_0202ea80(0x28, 1);
                if (func_0201b43c(p->unk_B4, 0x1770) != 0) {
                    code = 0x18;
                } else {
                    code = 0x16;
                }
            }
            break;
        case 0x20:
        case 0x21:
            if (r == 0) {
                code = 0x23;
            }
            break;
        case 0x23:
            func_020157d4(p, func_ov071_022790f0, 0xd, 1);
            func_02015828(p, 0);
            func_ov071_02279128(p, 0);
            break;
    }

    if (code != 0xff) {
        m = (u8) code;
        func_0206844c(p->unk_40, &m, dp);
    }
}
