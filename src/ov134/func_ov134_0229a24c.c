/* func_ov134_0229a24c @ 0x0229a24c, 0x14c bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

// The countdown field faf is volatile; it is read three times.

typedef struct UnkStruct_0229a24c {
    char pad_00[0x70];
    void *unk_70;
    int unk_74;
    int unk_78;
    char pad_7C[0x28];
    u8 unk_A4;
    u8 unk_A5;
    char pad_A6[3];
    u8 unk_A9;
    char pad_AA[5];
    volatile u8 unk_AF;
} UnkStruct_0229a24c;

extern u8 data_ov134_0229c03c[];
extern u8 data_ov134_0229c04c[];

extern void func_ov134_022995d4(UnkStruct_0229a24c *, u8);
extern void RtcSendPxiCommand(int);
extern void func_02001b7c(int);
extern void func_02001b6c(int);
extern void func_ov134_02299ecc(UnkStruct_0229a24c *);
extern void func_0200277c(u8);
extern void func_ov134_0229a918(UnkStruct_0229a24c *, u8, int);
extern int func_ov134_02299d10(UnkStruct_0229a24c *);
extern void func_02004658(int);
extern void func_ov134_0229a804(UnkStruct_0229a24c *);
extern int func_ov134_0229ac38(void);
extern void func_ov134_0229af60(UnkStruct_0229a24c *);

int func_ov134_0229a24c(UnkStruct_0229a24c *o)
{
    switch (o->unk_A9) {
        case 3:
            o->unk_A9 = 5;
            if (o->unk_A5 == 0) {
                o->unk_70 = data_ov134_0229c04c;
            } else {
                o->unk_70 = data_ov134_0229c03c;
            }
            break;
        case 4:
            o->unk_A9 = 5;
            break;
        case 5:
            if (o->unk_AF != 0) {
                o->unk_AF = o->unk_AF - 1;
                func_ov134_022995d4(o, o->unk_AF);
            } else {
                RtcSendPxiCommand(0x14);
                o->unk_A9 = 6;
                o->unk_AF = 3;
                func_02001b7c(1);
                o->unk_AF = o->unk_AF - 1;
                func_ov134_02299ecc(o);
            }
            break;
        case 6:
            if (o->unk_AF != 0) {
                o->unk_AF = o->unk_AF - 1;
                func_ov134_02299ecc(o);
            } else {
                func_0200277c(o->unk_A4);
                func_02001b6c(1);
                func_ov134_0229a918(o, o->unk_A5, 3);
                o->unk_74 = 0;
                o->unk_78 = 0;
                if (o->unk_70 != 0) {
                    if (func_ov134_02299d10(o)) {
                        o->unk_A9 = 7;
                        func_02004658(0x54);
                    } else {
                        o->unk_A9 = 8;
                    }
                    o->unk_70 = 0;
                    func_ov134_0229a804(o);
                } else {
                    o->unk_A9 = 8;
                }
            }
            break;
        case 7:
            if (func_ov134_0229ac38()) {
                func_ov134_0229af60(o);
                o->unk_A9 = 8;
            }
            break;
        case 8:
            return 1;
        case 0:
        case 1:
        case 2:
        default:
            break;
    }
    return 0;
}
