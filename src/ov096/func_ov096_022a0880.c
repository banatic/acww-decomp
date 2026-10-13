/* func_ov096_022a0880 @ 0x022a0880, 0x270 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0xac];
    u16 unk_AC;
    u16 unk_AE;
    u8 unk_B0;
    char pad_B1[3];
    u8 unk_B4;
    u8 unk_B5;
    char pad_B6[3];
    u8 unk_B9;
    char pad_BA[0xc0 - 0xba];
    u8 unk_C0;
    char pad_C1[0x358 - 0xc1];
    char unk_358[0x2418 - 0x358];
    char unk_2418[4];
} UnkStruct_022a0880;

extern int func_0206f56c(void);
extern void func_ov096_0229e898(UnkStruct_022a0880 *, int, int);
extern void func_ov096_022a18dc(UnkStruct_022a0880 *, int);
extern int func_ov002_02208008(UnkStruct_022a0880 *);
extern int func_ov096_0229c560(UnkStruct_022a0880 *, int, int);
extern void func_ov096_0229eb14(UnkStruct_022a0880 *);
extern void func_ov096_0229dd94(UnkStruct_022a0880 *);
extern void func_ov002_02207d24(void *, int);
extern int func_ov096_0229c310(UnkStruct_022a0880 *, int _x);
extern void func_ov096_0229c414(UnkStruct_022a0880 *);
extern void func_ov096_0229db78(UnkStruct_022a0880 *, int);
extern int func_ov096_0229f800(UnkStruct_022a0880 *);
extern int func_ov096_0229e4f8(UnkStruct_022a0880 *);
extern int func_ov096_0229e170(UnkStruct_022a0880 *, int);
extern void RtcSendPxiCommand(int);
extern int func_ov096_0229ef30(UnkStruct_022a0880 *, int, int, int);
extern int func_ov096_0229f820(UnkStruct_022a0880 *, int);
extern int func_ov096_0229f830(UnkStruct_022a0880 *, int);
extern u16 func_ov096_0229f0dc(UnkStruct_022a0880 *, int);
extern int func_ov096_0229f088(UnkStruct_022a0880 *, int);
extern int func_ov096_0229defc(UnkStruct_022a0880 *, u16 *, int, u16 *, int);
extern int func_ov096_0229f7ac(UnkStruct_022a0880 *, int);
extern void func_ov094_0229aa14(void *, int, int, int);
extern void func_ov096_0229db30(UnkStruct_022a0880 *, int);
extern int func_ov096_0229ee80(UnkStruct_022a0880 *, int);
extern void func_ov096_0229c2ec(UnkStruct_022a0880 *, int);
extern void func_ov096_0229ea5c(UnkStruct_022a0880 *);
extern void func_ov002_02207d00(void *);

extern struct {
    u16 h0;
    u16 h2;
} data_021fbe40;

void func_ov096_022a0880(UnkStruct_022a0880 *p)
{
    u16 h;
    int v;

    if (func_0206f56c() != 0) {
        func_ov096_0229e898(p, p->unk_B4, 1);
        func_ov096_022a18dc(p, 7);
        return;
    }
    if (func_ov096_0229c560(p, func_ov002_02208008(p), 1) != 0) {
        func_ov096_0229eb14(p);
        func_ov096_0229dd94(p);
        func_ov002_02207d24(p->unk_2418, 0);
        return;
    }
    if ((data_021fbe40.h2 & 1) != 0) {
        if (p->unk_B5 == 0x21) {
            if (func_ov096_0229c310(p, p->unk_B5) == 0) {
                return;
            }
            func_ov096_0229c414(p);
            func_ov096_0229db78(p, p->unk_B5);
            return;
        }
        if (func_ov096_0229f800(p) != 0) {
            if (p->unk_B5 == 0x24) {
                p->unk_C0 = (u8) func_ov096_0229e4f8(p);
                func_ov096_0229db78(p, p->unk_B5);
                return;
            }
            if (p->unk_B5 == 0x22) {
                func_ov096_0229c414(p);
                func_ov096_0229db78(p, p->unk_B5);
                return;
            }
            if (p->unk_B5 == 0x25) {
                if (func_ov096_0229e170(p, 1) == 0 && p->unk_B4 == 0x25) {
                    RtcSendPxiCommand(0x2a);
                    return;
                }
                func_ov096_0229c414(p);
                func_ov096_0229db78(p, p->unk_B5);
            }
            return;
        }
        if (func_ov096_0229ef30(p, p->unk_B5, p->unk_AC, p->unk_B0) != 0) {
            return;
        }
        if (func_ov096_0229f820(p, p->unk_B5) != 0) {
            func_ov096_0229c414(p);
        }
        if (func_ov096_0229f830(p, p->unk_B5) != 0) {
            h = func_ov096_0229f0dc(p, p->unk_B5);
            v = func_ov096_0229f088(p, p->unk_B5);
            if (func_ov096_0229defc(p, &p->unk_AC, p->unk_B0, &h, v) == 0) {
                func_ov094_0229aa14(p->unk_358, func_ov096_0229f7ac(p, p->unk_B5), h, v);
            }
        }
        if (func_ov096_0229f0dc(p, p->unk_B5) == 0xfff1) {
            func_ov096_0229db78(p, p->unk_B5);
            return;
        }
        if (p->unk_B9 != 0x26 && func_ov096_0229e170(p, 1) != 0) {
            p->unk_B9 = p->unk_B5;
            p->unk_AE = p->unk_AC;
        }
        func_ov096_0229db30(p, p->unk_B5);
        return;
    }
    if ((data_021fbe40.h2 & 2) != 0) {
        if (func_ov096_0229ee80(p, p->unk_B4) == 0) {
            func_ov096_0229db78(p, p->unk_B4);
        } else if (p->unk_B9 != 0x26) {
            v = p->unk_B4;
            p->unk_B4 = p->unk_B9;
            func_ov096_0229db78(p, p->unk_B4);
            p->unk_B9 = (u8) v;
            func_ov096_0229c2ec(p, 0x2000);
        }
    }
    func_ov096_0229ea5c(p);
    func_ov002_02207d00(p->unk_2418);
}
