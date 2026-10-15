/* func_ov113_0229a7ac @ 0x0229a7ac, 0xd4 bytes, Thumb, module ov113
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct CB {
    u8 pad_00[0x8d];
    u8 unk_8D;
    u8 pad_8E[0x0d];
    u8 unk_9B;
};

typedef void (CB::*PMF)();

extern "C" void func_0206f58c(void);
extern "C" int func_0206f56c(void);
extern "C" void func_ov113_0229a3fc(CB *self);
extern "C" void func_ov113_02299980(CB *self);
extern "C" int func_ov113_02299aa4(CB *self);
extern "C" void func_ov113_0229a390(CB *self);
extern const PMF data_ov113_0229abe8;
extern const PMF data_ov113_0229ab98;
extern const PMF data_ov113_0229ab90;
extern const PMF data_ov113_0229abb0;
extern const PMF data_ov113_0229abf0;

extern "C" int func_ov113_0229a7ac(CB *self)
{
    func_0206f58c();
    if (func_0206f56c() != 0) {
        if (self->unk_8D != 0) {
            if (self->unk_8D != 1) {
                goto else_path;
            }
        }
        self->unk_9B = 3;
        func_ov113_02299980(self);
        func_ov113_02299aa4(self);
        return 1;
    }
else_path:
    func_ov113_0229a3fc(self);
    static PMF tbl[5] = {data_ov113_0229abe8, data_ov113_0229ab98, data_ov113_0229ab90, data_ov113_0229abb0,
                         data_ov113_0229abf0};
    (self->*tbl[self->unk_8D])();
    func_ov113_0229a390(self);
    return 1;
}
