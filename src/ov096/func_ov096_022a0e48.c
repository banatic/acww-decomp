/* func_ov096_022a0e48 @ 0x022a0e48, 0x210 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0x8d];
    u8 unk_8D;
    char pad_8E[0xa4 - 0x8e];
    char *unk_A4;
    char *unk_A8;
    char pad_AC[0xb4 - 0xac];
    u8 unk_B4;
    char pad_B5[0xc0 - 0xb5];
    u8 unk_C0;
} UnkStruct_022a0e48;

extern int func_0206f56c(void);
extern void func_ov096_0229e898(UnkStruct_022a0e48 *, int, int);
extern int func_ov096_022a18dc(UnkStruct_022a0e48 *, int);
extern void func_ov096_0229ea88(UnkStruct_022a0e48 *);
extern void func_ov096_0229ed44(UnkStruct_022a0e48 *);
extern int func_ov096_0229f75c(UnkStruct_022a0e48 *, char *, char *, int);
extern int func_ov096_0229f4f8(UnkStruct_022a0e48 *, char *, char *, int);
extern int func_ov096_0229ee9c(UnkStruct_022a0e48 *, int, int);
extern int func_ov096_0229f820(UnkStruct_022a0e48 *, int);
extern void func_ov096_0229c414(UnkStruct_022a0e48 *);
extern int func_ov096_0229f650(UnkStruct_022a0e48 *, int);
extern void func_ov096_0229fb9c(UnkStruct_022a0e48 *);
extern int func_ov096_0229f830(UnkStruct_022a0e48 *, int);
extern void func_ov094_022999d8(void);
extern unsigned char *func_ov096_0229f90c(UnkStruct_022a0e48 *, int, int);
extern void func_ov096_0229ec90(UnkStruct_022a0e48 *, int);
extern u8 func_ov096_0229f3d4(UnkStruct_022a0e48 *, char *, char *);
extern int func_ov096_0229e6b0(UnkStruct_022a0e48 *);
extern int func_ov096_0229e71c(UnkStruct_022a0e48 *);
extern int func_ov096_0229e4f8(UnkStruct_022a0e48 *);
extern void func_ov096_0229e29c(UnkStruct_022a0e48 *);
extern void func_ov096_0229e67c(UnkStruct_022a0e48 *);
extern int func_ov096_0229e170(UnkStruct_022a0e48 *, int);
extern int func_ov096_0229e1ec(UnkStruct_022a0e48 *);
extern int func_ov096_0229f460(UnkStruct_022a0e48 *, char *, char *);
extern int func_ov096_0229c310(UnkStruct_022a0e48 *);
extern void func_ov096_0229c348(UnkStruct_022a0e48 *);

extern u8 data_021fbdd8;

void func_ov096_022a0e48(UnkStruct_022a0e48 *p)
{
    char *a;
    char *b;
    int r;
    u8 q;

    if (func_0206f56c() != 0) {
        func_ov096_0229e898(p, p->unk_B4, 1);
        func_ov096_022a18dc(p, 7);
        return;
    }
    func_ov096_0229ea88(p);
    func_ov096_0229ed44(p);
    a = p->unk_A4 + 8;
    b = p->unk_A8 + 8;
    r = func_ov096_0229f75c(p, a, b, 0);
    if (r == 0x26) {
        r = func_ov096_0229f4f8(p, a, b, 0);
    }
    if (r != 0x26) {
        if (data_021fbdd8 == 0) {
            if (func_ov096_0229ee9c(p, r, p->unk_B4) == 0) {
                if (func_ov096_0229f820(p, r) != 0) {
                    func_ov096_0229c414(p);
                }
                func_ov096_0229f650(p, r);
                if (p->unk_8D == 5) {
                    func_ov096_0229fb9c(p);
                }
                if (func_ov096_0229f830(p, r) != 0 || func_ov096_0229f820(p, r) != 0) {
                    func_ov094_022999d8();
                }
            } else {
                func_ov096_0229f90c(p, p->unk_B4, 4);
            }
        } else {
            func_ov096_0229ec90(p, r);
        }
        return;
    }

    q = func_ov096_0229f3d4(p, a, b);
    if (q != 0x26) {
        if (data_021fbdd8 == 0) {
            if (q == 0x22 || q == 0x23) {
                if (func_ov096_0229e6b0(p) == 0) {
                    func_ov096_0229f90c(p, p->unk_B4, 4);
                    return;
                }
                if (func_ov096_0229e71c(p) != 0) {
                    func_ov096_0229fb9c(p);
                }
            } else if (q == 0x24) {
                p->unk_C0 = (u8) func_ov096_0229e4f8(p);
                if (p->unk_C0 < 1) {
                    func_ov096_0229e29c(p);
                    return;
                }
                if (p->unk_C0 == 1) {
                    func_ov096_0229f90c(p, p->unk_B4, 4);
                    return;
                }
                func_ov096_0229e67c(p);
            } else if (q == 0x25) {
                if (func_ov096_0229e170(p, 0) != 0) {
                    func_ov096_0229e1ec(p);
                    return;
                }
                func_ov096_0229f90c(p, p->unk_B4, 4);
            } else {
                func_ov096_0229f90c(p, p->unk_B4, 4);
            }
        } else {
            func_ov096_0229ec90(p, q);
        }
        return;
    }

    if (func_ov096_0229f460(p, a, b) != 0) {
        if (data_021fbdd8 == 0) {
            if (func_ov096_0229c310(p) != 0) {
                func_ov096_0229c348(p);
                func_ov096_0229fb9c(p);
            } else {
                func_ov096_0229f90c(p, p->unk_B4, 4);
            }
        } else {
            func_ov096_0229ec90(p, 0x21);
        }
        return;
    }
    if (data_021fbdd8 == 0) {
        func_ov096_0229f90c(p, p->unk_B4, 4);
    }
}
