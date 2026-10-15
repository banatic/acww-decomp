/* func_ov133_0229c420 @ 0x0229c420, 0x16c bytes, Thumb, module ov133
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0229c420;
typedef void (UnkStruct_0229c420::*PMF)(void);

struct UnkStruct_0229c420 {
    u8 pad_00[0x8d];
    u8 unk_8D;
};

extern PMF data_ov133_0229c8f0, data_ov133_0229c8e8, data_ov133_0229c8e0, data_ov133_0229c8d8, data_ov133_0229c8d0,
    data_ov133_0229c888, data_ov133_0229c8c0, data_ov133_0229c8b8, data_ov133_0229c8b0, data_ov133_0229c8a8,
    data_ov133_0229c8f8, data_ov133_0229c898, data_ov133_0229c890;

extern "C" void func_0206f58c(void);
extern "C" int func_0206f56c(void);
extern "C" void func_ov133_0229ba10(UnkStruct_0229c420 *self);
extern "C" void func_ov002_02208090(UnkStruct_0229c420 *self, int v);
extern "C" int func_ov133_0229c3d4(UnkStruct_0229c420 *self, int v);
extern "C" int func_0206fca4(void);
extern "C" void *func_ov133_0229b714(UnkStruct_0229c420 *self);
extern "C" void func_02077c40(void *p);
extern "C" unsigned char *func_ov002_022080a0(UnkStruct_0229c420 *self, unsigned char value);

extern "C" void func_ov133_0229c420(UnkStruct_0229c420 *self)
{
    static PMF tbl[13] = {data_ov133_0229c8f0, data_ov133_0229c8e8, data_ov133_0229c8e0, data_ov133_0229c8d8,
                          data_ov133_0229c8d0, data_ov133_0229c888, data_ov133_0229c8c0, data_ov133_0229c8b8,
                          data_ov133_0229c8b0, data_ov133_0229c8a8, data_ov133_0229c8f8, data_ov133_0229c898,
                          data_ov133_0229c890};

    func_0206f58c();
    if (func_0206f56c()) {
        switch (self->unk_8D) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 7:
            case 8:
            case 9:
                func_ov133_0229ba10(self);
                func_ov002_02208090(self, 3);
                func_ov133_0229c3d4(self, 7);
                if (func_0206fca4() == 0xe) {
                    func_02077c40(func_ov133_0229b714(self));
                }
                func_ov002_022080a0(self, 1);
                break;
            case 4:
            case 5:
            case 6:
                break;
        }
    }
    (self->*tbl[self->unk_8D])();
}
