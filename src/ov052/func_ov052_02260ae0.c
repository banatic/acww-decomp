/* func_ov052_02260ae0 @ 0x02260ae0, 0x13c bytes, Thumb, module ov052
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02260ae0 {
    char pad_00[0x1e];
    u8 unk_1E;
    char pad_1F[0x40 - 0x1f];
    void *unk_40;
    char pad_44[0xb4 - 0x44];
    char *unk_B4;
    char pad_B8[0xbc - 0xb8];
    int unk_BC;
} UnkStruct_02260ae0;

typedef struct Msg {
    u8 unk_00;
    u16 unk_02;
    u16 unk_04;
    u16 unk_06;
} Msg;

extern void *func_020984e8(void);
extern void func_020154b4(UnkStruct_02260ae0 *, u16 *, int, int, int);
extern void func_02015330(UnkStruct_02260ae0 *, u16 *, int, int, int);
extern void func_0209a000(u16 *, int);
extern int func_02099020(void *, int);
extern void func_ov052_022610cc(UnkStruct_02260ae0 *, int);
extern void func_0201b420(char *, int);
extern void func_02098ff8(void *, int);
extern void func_0202ea80(int, int);
extern void func_ov052_022608b4(UnkStruct_02260ae0 *);
extern void func_0206844c(void *, u8 *, const void *);
extern const int data_ov052_02261e50;

void func_ov052_02260ae0(UnkStruct_02260ae0 *this)
{
    Msg m;
    const void *tag = (const void *) &data_ov052_02261e50;
    int code = 0xff;
    void *a = func_020984e8();
    int st = this->unk_1E;

    switch (st) {
        case 0x2e:
            m.unk_02 = 0x36fc;
            func_020154b4(this, &m.unk_02, 0, 5, 0);
            m.unk_04 = 0x36fc;
            func_0209a000(&m.unk_04, 0);
            code = 0x2f;
            // fallthrough
        case 0x2d:
            this->unk_BC = ~1;
            break;
        case 6:
            if (func_02099020(a, 0xc) == 0) {
                func_ov052_022610cc(this, 3);
            } else {
                func_ov052_022610cc(this, 0xa);
            }
            break;
        case 7:
            func_ov052_022610cc(this, 4);
            break;
        case 0x10:
            m.unk_06 = 0x149d;
            func_02015330(this, &m.unk_06, 0, 5, 0);
            *(u16 *) (this->unk_B4 + 0x71e) = 0xfff1;
            code = 0x11;
            func_0201b420(this->unk_B4, 0xbb8);
            func_ov052_022610cc(this, 7);
            func_02098ff8(a, 0xc);
            func_0202ea80(1, 1);
            break;
        case 0x24:
        case 0x25:
        case 0x26:
        case 0x27:
        case 0x28:
            func_ov052_022608b4(this);
            break;
    }
    if (code != 0xff) {
        m.unk_00 = (u8) code;
        func_0206844c(this->unk_40, &m.unk_00, tag);
    }
}
