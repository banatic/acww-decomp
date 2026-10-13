/* func_020709c4 @ 0x020709c4, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_020709c4 {
    u32 pad_00[4];
    int unk_10;
    u32 pad_14[7];
    int unk_30;
};

class UnkStruct_020709c4_2 {
  public:
    virtual int m0();
    virtual int m1();
    virtual int m2();
    virtual int m3();
    unsigned char pad_04[0x64];
    UnkStruct_020709c4 *s;
};

extern "C" void func_02051648(UnkStruct_020709c4 *s);
extern "C" void func_02051694(UnkStruct_020709c4 *s);

extern "C" void func_020709c4(UnkStruct_020709c4_2 *obj, int flag, int add)
{
    UnkStruct_020709c4 *sp = obj->s;
    if (sp) {
        sp->unk_10 = obj->m3();
        if (flag) {
            func_02051648(obj->s);
        } else {
            obj->s->unk_30 = 0;
        }
        obj->s->unk_30 += add;
        func_02051694(obj->s);
    }
}
