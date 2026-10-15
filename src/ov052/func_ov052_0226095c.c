/* func_ov052_0226095c @ 0x0226095c, 0x184 bytes, Thumb, module ov052
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_020160b4(void *);
extern int func_020ab504(int);
extern int func_0201b43c(int, int);
extern int func_02099fe8(void);
extern void func_0209a050(void *parameter0);
extern int func_02015330(void *, u16 *, int, int, int);
extern int func_ov052_02261158(int, int, int);
extern int func_ov052_0226118c(int, int, int);
extern void MI_CpuFill8(void *, int, int);
extern void func_0206844c(int, u8 *, void *);
extern char data_ov052_02261e50;

typedef struct {
    char pad_00[0x1e];
    u8 unk_1E;
    char pad_1F[0x21];
    int unk_40;
    char pad_44[0x70];
    int unk_B4;
    int unk_B8;
    int unk_BC;
    u8 unk_C0;
} UnkStruct_0226095c;

void func_ov052_0226095c(UnkStruct_0226095c *p)
{
    struct {
        u8 b;
        u16 h;
    } m;
    int r;
    void *dp;
    int code;
    int v;

    r = func_020ab504(func_020160b4(p));
    dp = &data_ov052_02261e50;
    code = 0xff;
    v = p->unk_1E;
    switch (v) {
        case 0x2c:
            if (r == 0) {
                if (p->unk_BC >= 0) {
                    func_0209a050((void *) (*(
                        int *) ((char *) (((unsigned int) (((unsigned int) (((unsigned int) (p) + (0x0))) + (0x0))) +
                                           (0xbc))) +
                                0)));
                    m.h = 0x34a8;
                    func_02015330(p, &m.h, 0, 5, 0);
                }
                code = 0x2e;
            }
            break;
        case 7:
        case 0x12:
            if (r != 0) {
                if (func_0201b43c(p->unk_B4, 0xbb8) == 0) {
                    code = 0xa;
                } else if (p->unk_C0 == 0) {
                    code = 8;
                } else {
                    code = 0xc;
                }
            }
            break;
        case 9:
            p->unk_C0 = 1;
            if (r == 0) {
                code = 0xc;
            }
            break;
        case 0x1d:
        case 0x1e:
        case 0x1f:
        case 0x20:
        case 0x21:
        case 0x22:
            if (r == 0) {
                if (func_0201b43c(p->unk_B4, p->unk_B8) != 0) {
                    if (func_02099fe8() >= 0) {
                        int idx = func_ov052_02261158(p->unk_B4, p->unk_B4 + 0x738, 5);
                        *(u8 *) (p->unk_B4 + idx + 0x738) = 1;
                        if (func_ov052_0226118c(p->unk_B4, p->unk_B4 + 0x738, 5) == 0) {
                            MI_CpuFill8((void *) (p->unk_B4 + 0x738), 0, 5);
                            *(u8 *) (p->unk_B4 + idx + 0x738) = 1;
                        }
                        code = (u8) (idx + 0x24);
                        break;
                    }
                    code = 0x2a;
                } else {
                    code = 0x29;
                }
            }
            *(u16 *) (p->unk_B4 + 0x71e) = 0xfff1;
            break;
    }

    if (code != 0xff) {
        m.b = (u8) code;
        func_0206844c(p->unk_40, &m.b, dp);
    }
}
