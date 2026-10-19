/* func_ov053_02260894 @ 0x02260894, 0x168 bytes, Thumb, module ov053
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02260894 {
    u8 pad_00[0x1e];
    u8 state;
    u8 pad_1F[0x40 - 0x1f];
    void *unk_40;
    u8 pad_44[0xb4 - 0x44];
    void *unk_B4;
    u8 unk_B8;
    u8 unk_B9;
    u8 unk_BA;
    u8 unk_BB;
    u8 unk_BC;
    u8 unk_BD;
} UnkStruct_02260894;

extern void *func_020984e8(void);
extern void *func_02099870(void *);
extern int func_020950c0(void *);
extern int func_ov004_0222c1b0(int);
extern void func_0200467c(int);
extern int func_ov053_0226075c(void *receiver);
extern void func_ov053_02261524(void *, int);
extern int func_0202ea80(int, int);
extern void *func_0208602c(void);
extern void func_020860d4(void *, int);
extern void func_0206844c(void *, u8 *, const void *);

extern void *data_ov053_02261980;
extern u8 data_ov053_022617ec[][2];
extern u8 data_021f43e8[];

void func_ov053_02260894(UnkStruct_02260894 *obj)
{
    u8 m;
    void *h;
    const void *tag;
    int code;
    int v;

    h = func_020984e8();
    tag = data_ov053_02261980;
    code = 0xff;

    switch (obj->state) {
        case 0xd:
            if (obj->unk_BA == obj->unk_BC && obj->unk_BB == obj->unk_BD) {
                code = 0x37;
            } else {
                code = 0xe;
            }
            obj->unk_B9 = 0;
            break;
        case 0x17:
            obj->unk_B8 = 1;
            break;
        case 0x18:
            obj->unk_B8 = 0;
            break;
        case 0x2f:
        case 0x30:
        case 0x31:
        case 0x32:
        case 0x33:
        case 0x34:
        case 0x35:
        case 0x36:
            v = func_020950c0(func_02099870(h));
            if (obj->unk_B8 != 0) {
                v = (v == 0) ? 1 : 0;
            }
            obj->unk_BA = data_ov053_022617ec[obj->state - 0x2f][v];
            break;
        case 0x40:
            func_ov004_0222c1b0(0);
            func_0200467c(0x43);
            code = func_ov053_0226075c((void *) obj);
            break;
        case 0x42:
            func_ov053_02261524(obj->unk_B4, 9);
            break;
        case 0xe:
        case 0x37:
            func_0202ea80(0x13, 1);
            func_020860d4(func_0208602c(), 7);
            func_0206844c(obj->unk_40, data_021f43e8, 0);
            break;
        case 0x41:
            func_ov004_0222c1b0(1);
            func_0200467c(0x44);
            break;
        case 0x45:
            break;
    }

    if (code != 0xff) {
        m = (u8) code;
        func_0206844c(obj->unk_40, &m, tag);
    }
}
