/* func_ov129_0229cd54 @ 0x0229cd54, 0x208 bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0x94];
    int unk_94;
    int unk_98;
    char pad_9C[0xae - 0x9c];
    u8 unk_AE;
    char pad_AF[0x1d4 - 0xaf];
    char unk_1D4[0x3a0 - 0x1d4];
    char unk_3A0[0x734 - 0x3a0];
    char unk_734[4];
} UnkStruct_0229cd54;

extern int func_ov002_02208014(void *receiver);
extern void func_ov129_0229c874(UnkStruct_0229cd54 *);
extern void func_ov129_0229c328(UnkStruct_0229cd54 *);
extern void func_ov129_0229b7cc(UnkStruct_0229cd54 *, int);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov129_0229c39c(UnkStruct_0229cd54 *);
extern void func_ov129_0229c2d8(UnkStruct_0229cd54 *);
extern int func_ov002_0220a620(void *, int);
extern void func_ov129_0229c3f4(UnkStruct_0229cd54 *);
extern void func_ov129_0229c79c(UnkStruct_0229cd54 *);
extern void func_ov129_0229c758(UnkStruct_0229cd54 *);
extern void func_ov127_02299b58(void *, int);
extern void func_ov129_0229b7dc(UnkStruct_0229cd54 *, int);
extern int func_ov127_02299abc(void *, int, int);
extern void func_ov129_0229c1f8(UnkStruct_0229cd54 *);
extern void func_ov002_0220a0b4(void *, int, int);

extern struct {
    u16 h0;
    u16 h2;
} data_021fbe40;

void func_ov129_0229cd54(UnkStruct_0229cd54 *p)
{
    int x0;
    int y0;

    if (func_ov002_02208014(p) != 0) {
        func_ov129_0229c874(p);
        return;
    }
    if ((data_021fbe40.h2 & 1) != 0) {
        func_ov129_0229c328(p);
        return;
    }
    if ((data_021fbe40.h2 & 0x800) != 0) {
        func_ov129_0229b7cc(p, 2);
        func_ov002_02208098((void *) (p), 4);
        func_ov129_0229c39c(p);
        func_ov129_0229c2d8(p);
        return;
    }
    if ((data_021fbe40.h2 & 8) != 0) {
        if (func_ov002_0220a620(p->unk_1D4, 6) != 0) {
            return;
        }
        func_ov129_0229b7cc(p, 2);
        p->unk_AE = 4;
        func_ov129_0229c2d8(p);
        func_ov129_0229c3f4(p);
        func_ov129_0229c79c(p);
        return;
    }
    if ((data_021fbe40.h2 & 2) != 0) {
        func_ov129_0229b7cc(p, 2);
        p->unk_AE = 5;
        func_ov129_0229c2d8(p);
        func_ov129_0229c3f4(p);
        func_ov129_0229c758(p);
        return;
    }

    x0 = p->unk_94;
    y0 = p->unk_98;
    if ((data_021fbe40.h0 & 0x20) != 0) {
        p->unk_94 = p->unk_94 - 4;
    } else if ((data_021fbe40.h0 & 0x10) != 0) {
        p->unk_94 = p->unk_94 + 4;
    }
    if ((data_021fbe40.h0 & 0x40) != 0) {
        p->unk_98 = p->unk_98 - 4;
    } else if ((data_021fbe40.h0 & 0x80) != 0) {
        p->unk_98 = p->unk_98 + 4;
    }
    if (x0 == p->unk_94 && y0 == p->unk_98) {
        return;
    }
    if (p->unk_94 < 0x30) {
        p->unk_94 = 0x30;
        func_ov127_02299b58(p->unk_734, -4);
        func_ov129_0229b7dc(p, 0x40);
    } else if (p->unk_94 > 0xd0) {
        p->unk_94 = 0xd0;
        func_ov127_02299b58(p->unk_734, 4);
        func_ov129_0229b7dc(p, 0x40);
    }
    if (p->unk_98 < 0x1c) {
        p->unk_98 = 0x1c;
        if (func_ov127_02299abc(p->unk_734, -4, 0) != 0) {
            func_ov129_0229b7dc(p, 0x40);
        }
    } else if (p->unk_98 > 0xac) {
        p->unk_98 = 0xac;
        if (func_ov127_02299abc(p->unk_734, 4, 0) != 0) {
            func_ov129_0229b7dc(p, 0x40);
        }
    }
    func_ov129_0229c1f8(p);
    func_ov002_0220a0b4(p->unk_3A0, p->unk_94, p->unk_98);
}
