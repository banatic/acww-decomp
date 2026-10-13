/* func_ov004_0220c078 @ 0x0220c078, 0x48 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov004_0224fc4c19func_ov004_0220c078Ev
 */

#include "cpp/ov004/Obj_ov004_0224fc4c.h"

extern "C" void func_0203ee14(Base_0203f080 *self, Base_02066994 *recv);
extern "C" void func_020a8164(Base_02066994 &recv, void *name);
extern "C" void func_ov004_0220c250(Obj_ov004_0224fc4c *self);
extern "C" void *data_ov004_0224fbe0;

struct UnkStruct_0220c078 {
    char pad_00[8];
    unsigned int unk_08;
};

// The empty destructor keeps the eight bytes the ROM reserves for this local.
class Scope {
  public:
    Scope() {}
    ~Scope() {}
};

int Obj_ov004_0224fc4c::func_ov004_0220c078()
{
    Scope scope;
    func_0203ee14(this, this);
    func_020a8164(*this, data_ov004_0224fbe0);
    unk_1E = 0;
    func_ov004_0220c250(this);
    ((UnkStruct_0220c078 *) unk_40)->unk_08 = 1;
    return 1;
}
