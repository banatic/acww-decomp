/* func_02015688 @ 0x02015688, 0xd6 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

// Both guards nest into one if, sharing the return 0 with the switch fallthrough.

typedef struct UnkStruct_02015688 {
    char pad_00[4];
    int unk_04;
    int unk_08;
} UnkStruct_02015688;

typedef struct UnkStruct_02015688_2 {
    char pad_00[0x40];
    UnkStruct_02015688 *unk_40;
    char pad_44[0x24];
    u32 unk_68;
    int unk_6C;
    int unk_70;
    int unk_74;
    int (*unk_78)(u16 *, int);
    u16 unk_7C;
    char pad_7E[6];
    u8 unk_84;
    char pad_85[1];
    u8 unk_86;
    u8 unk_87;
    u8 unk_88;
    char pad_89[0x13];
    int unk_9C;
    int unk_A0;
    char pad_A4[8];
    u8 unk_AC;
} UnkStruct_02015688_2;

extern u16 func_0206f9d8(int (*)(u16 *, int));
extern int func_0206fa28(int, u8);
extern int func_0206f99c(void);
extern int func_0206fbf8(u8);
extern int func_0206fbd8(u8, u8);
extern int func_0206f7dc(int, int);
extern int func_0206ffe8(int);
extern int func_0206f640(u8, int, int);

int func_02015688(UnkStruct_02015688_2 *o)
{
    UnkStruct_02015688 *p;
    int r;
    int v;

    p = o->unk_40;
    if (p != 0 && p->unk_04 == 5) {
        r = 0;
        switch (o->unk_68) {
            case 0:
                v = o->unk_7C;
                if (o->unk_78 != 0) {
                    v = func_0206f9d8(o->unk_78);
                }
                r = func_0206fa28(v, o->unk_84);
                break;
            case 1:
                o->unk_88 = 1;
                r = func_0206f99c();
                break;
            case 2:
                r = func_0206fbf8(o->unk_86);
                break;
            case 3:
                r = func_0206fbd8(o->unk_86, o->unk_87);
                break;
            case 4:
                r = func_0206f7dc(o->unk_6C, o->unk_70);
                break;
            case 5:
                r = func_0206ffe8(o->unk_74);
                break;
            case 6:
                r = func_0206f640(o->unk_86, o->unk_9C, o->unk_A0);
                break;
            case 7:
                if (o->unk_88 != 1) {
                    p->unk_08 = 1;
                }
                o->unk_AC = 3;
                return 1;
        }
        if (r != 0) {
            o->unk_AC = 2;
        }
    }
    return 0;
}
