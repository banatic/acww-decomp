/* func_ov090_022993cc @ 0x022993cc, 0x8c bytes, Thumb, module ov090
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_022993cc {
    u8 pad_00[0x93];
    u8 unk_93;
    u8 unk_94;
    u8 unk_95;
    u8 pad_96;
    u8 unk_97;
    u8 unk_98;
} UnkStruct_022993cc;

extern void func_ov090_02298fac(UnkStruct_022993cc *self, u32 p);
extern void func_0206efc0(void);
extern void RtcSendPxiCommand(int a);
extern char *data_021c526c;
extern void func_02036468(void *p);
extern void func_0206fbb4(void);

void func_ov090_022993cc(UnkStruct_022993cc *self, u32 p)
{
    u8 v;

    self->unk_98 = 0;
    v = self->unk_93;
    func_ov090_02298fac(self, p);

    if (p == 7) {
        self->unk_94 = 0;
        if (self->unk_97 == 1) {
            self->unk_97 = 2;
        }
        if (self->unk_97 == 0) {
            func_0206efc0();
        }
        RtcSendPxiCommand(2);
        func_02036468(data_021c526c + 0x1c4);
    } else if (p <= 6 && v <= 6) {
        RtcSendPxiCommand(3);
    }

    if (p == 0) {
        func_0206fbb4();
    }

    if (v <= 6 && p <= 6) {
        self->unk_95 = 1;
    }
}
