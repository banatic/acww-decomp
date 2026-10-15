/* func_ov071_02278c4c @ 0x02278c4c, 0x1f4 bytes, Thumb, module ov071
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_020984e8(void);
extern void func_0208b520(void);
extern void func_0208b514(void);
extern int func_02099020(int, int);
extern void func_02098ff8(int, int);
extern int func_02099670(int);
extern void func_02088a78(void *);
extern int func_0202ea80(int, int);
extern int func_ov071_02278fd0(int, int, int);
extern void MI_CpuFill8(void *, int, int);
extern int func_02015330(void *, u16 *, int, int, int);
extern void func_0201b420(int, int);
extern void func_020157d4(void *self, int (*predicate)(unsigned short *, int), unsigned char kind, unsigned char flag);
extern int func_02015828(void *, int);
extern int func_02015094(void *);
extern void func_ov071_02279128(void *, int);
extern unsigned short func_ov071_022790f0(unsigned short *argument0, int argument1);
extern unsigned short func_0206f9d8(int (*predicate)(unsigned short *, int));
extern void func_0206844c(int, u8 *, void *);
extern char data_ov071_0227a180;

typedef struct {
    char pad_00[0x1e];
    u8 unk_1E;
    char pad_1F[0x21];
    int unk_40;
    char pad_44[0x70];
    int unk_B4;
    u8 unk_B8;
} UnkStruct_02278c4c;

#define TilePredicate_func_ov071_022790f0 ((int (*)(unsigned short *, int)) func_ov071_022790f0)

void func_ov071_02278c4c(UnkStruct_02278c4c *p)
{
    struct {
        u8 b;
        u8 pad;
        u16 h2;
        u16 h4;
    } m;
    void *dp;
    int code;
    int g;

    dp = &data_ov071_0227a180;
    code = 0xff;
    g = func_020984e8();
    switch (p->unk_1E) {
        case 5:
        case 0x14:
        case 0x1c:
            func_0208b520();
            code = 0x15;
            if (func_02099020(g, 0x17) != 0) {
                code = 0x1d;
            }
            break;
        case 0xd:
        case 0xe:
        case 0xf:
        case 0x10:
        case 0x11:
        case 0x12: {
            int idx = func_ov071_02278fd0(p->unk_B4, p->unk_B4 + 0x724, 5);
            u8 *q = (u8 *) (p->unk_B4 + 0x724);
            if (q[idx] == 0) {
                q[idx] = 1;
            }
            code = (u8) (idx + 0xe);
        }
            p->unk_B8 = (u8) (p->unk_B8 + 1);
            if (p->unk_B8 >= 4) {
                if (func_02099020(g, 0x18) == 0) {
                    code = 0x13;
                } else {
                    code = 0x1b;
                    func_0202ea80(0x28, 1);
                }
                p->unk_B8 = 0;
                MI_CpuFill8((void *) (p->unk_B4 + 0x724), 0, 5);
            }
            break;
        case 0x13:
            if (func_02099020(g, 0x17) == 0) {
                code = 0x14;
            } else {
                code = 0x1c;
            }
            break;
        case 0x18:
            if (func_02099020(g, 0x17) == 0) {
                code = 0x19;
            } else {
                code = 0x1e;
            }
            break;
        case 0x19:
            m.h2 = 0x149d;
            func_02015330(p, &m.h2, 0, 5, 0);
            func_0201b420(p->unk_B4, 0xbb8);
            code = 0x1a;
            func_02098ff8(g, 0x17);
            func_02088a78((void *) func_02099670(g));
            break;
        case 0x16:
        case 0x1a:
        case 0x1f:
            func_0208b514();
            break;
        case 0x1e:
            m.h4 = 0x14a0;
            func_02015330(p, &m.h4, 0, 5, 0);
            func_0201b420(p->unk_B4, 0x1770);
            code = 0x1f;
            func_02098ff8(g, 0x18);
            break;
        case 0x23:
            func_020157d4(p, TilePredicate_func_ov071_022790f0, 0xd, 1);
            func_02015828(p, 0);
            func_ov071_02279128(p, 0);
            break;
        case 0x25:
            func_02015094(p);
            if (func_0206f9d8(TilePredicate_func_ov071_022790f0) != 0) {
                code = 0x21;
            } else {
                code = 0x26;
            }
            break;
    }

    if (code != 0xff) {
        m.b = (u8) code;
        func_0206844c(p->unk_40, &m.b, dp);
    }
}

#undef TilePredicate_func_ov071_022790f0
