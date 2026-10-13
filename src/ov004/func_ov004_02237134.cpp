/* func_ov004_02237134 @ 0x02237134, 0xe4 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02237134;
typedef void (UnkStruct_02237134::*PMF)(void);

struct UnkStruct_02237134 {
    u8 pad_00[0x15c];
    int unk_15C;
    u8 pad_160[0x1a8 - 0x160];
    int unk_1A8;
    u8 pad_1AC[0x1c0 - 0x1ac];
    s16 unk_1C0;
    u8 pad_1C2[0x1e8 - 0x1c2];
    u8 unk_1E8;
    u8 pad_1E9[0x1ee - 0x1e9];
    u8 unk_1EE;
    u8 pad_1EF[0x1fc - 0x1ef];
    u8 unk_1FC;
    u8 pad_1FD[0x252 - 0x1fd];
    u8 unk_252;
    u8 pad_253[0x258 - 0x253];
    int unk_258;
};

extern "C" {
extern PMF data_ov004_0225949c[];
extern void *data_ov004_022594d4[];
extern void func_ov004_02239768(struct UnkStruct_02237134 *self);
extern void func_ov004_022396a0(struct UnkStruct_02237134 *self);
extern void func_ov004_0223592c(struct UnkStruct_02237134 *self);
extern int func_ov004_02239424(void *a, void *b, void *c, int d);
extern void func_ov004_02239b80(struct UnkStruct_02237134 *self);
extern void func_ov004_0223635c(struct UnkStruct_02237134 *self, void *p);
extern void func_ov004_02236418(struct UnkStruct_02237134 *self);
void func_ov004_02237134(struct UnkStruct_02237134 *self);
}

void func_ov004_02237134(struct UnkStruct_02237134 *self)
{
    u8 v;

    if (self->unk_1EE != 2 && self->unk_1EE != 6) {
        func_ov004_02239768(self);
        func_ov004_022396a0(self);
    }
    (self->*data_ov004_0225949c[self->unk_1EE])();
    func_ov004_0223592c(self);
    if (func_ov004_02239424(&self->unk_1C0, &self->unk_1A8, &self->unk_258, 0x1000) != 0) {
        func_ov004_02239b80(self);
    } else if (self->unk_1FC != 0) {
        self->unk_1EE = 2;
        self->unk_1FC = 0;
    }
    v = self->unk_1E8;
    if (self->unk_252 != v && v != self->unk_15C) {
        self->unk_252 = v;
        if (self->unk_1EE != 1) {
            func_ov004_0223635c(self, (u8 *) data_ov004_022594d4[self->unk_1E8] + 0x1a8);
        }
    }
    func_ov004_02236418(self);
}
