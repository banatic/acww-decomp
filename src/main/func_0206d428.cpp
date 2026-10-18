/* func_0206d428 @ 0x0206d428, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

class Entry {
  public:
    virtual int f0()
    {
        return 0;
    }
    virtual int f1()
    {
        return 0;
    }
    virtual int f2()
    {
        return 0;
    }
    virtual int f3();
    u8 data[0x58];
};

struct Work {
    u8 pre[0x18ac];
    Entry entries[1];
    u8 pad_1908[0x150];
    u32 unk_1A58[2];
    u32 unk_1A60;
};

struct UnkStruct_0206d428 {
    u8 pre[0x2c];
    Work *wrk;
};

extern "C" void func_020a9334(UnkStruct_0206d428 *self, int v);
extern "C" void func_0206d4e0(UnkStruct_0206d428 *self, Entry *e);
extern "C" void func_020a7994(void *p, int v);

extern "C" void func_0206d428(UnkStruct_0206d428 *self, int index)
{
    Entry *e = &self->wrk->entries[index];
    int v = e->f3();
    func_020a9334(self, v);
    func_0206d4e0(self, e);
    v = e->f3();
    func_020a7994(self->wrk->unk_1A58, v);
    self->wrk->unk_1A60 = 0;
}
