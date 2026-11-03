/* fox_3: 3 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0221be34 @ 0x0221be34, 0x48 bytes, Thumb, emits _ZN18Obj_ov003_0223863019func_ov003_0221be34Ev
 * func_ov003_0221bd90 @ 0x0221bd90, 0xa4 bytes, Thumb, emits _ZN18Obj_ov003_0223863019func_ov003_0221bd90Ev
 * func_ov003_0221bd6c @ 0x0221bd6c, 0x24 bytes, Thumb, emits _ZN18Obj_ov003_0223863019func_ov003_0221bd6cEv
 */

#include "cpp/ov003/Obj_ov003_02238630.h"

extern "C" int func_020b2470(int);

// Local of the talk-start sequence; its inline destructor keeps an 8-byte frame slot.
struct D {
    int a, b;
    ~D() {}
};

struct UnkStruct_0221bd90 {
    char pad[8];
    int unk_08;
};

extern "C" {
extern char data_ov003_02238778[];
void func_0203ee14(Base_0203f080 *self, Base_02066994 *recv);
void func_020a8164(Base_02066994 &recv, const char *name);
void func_02066914(Base_02066994 &recv, int arg);
void func_020b23ec(int a, int b);
int func_020ae2c4(void);
}

struct UnkStruct_0221bd6c {
    int pad_00;
    void *unk_04;
};

void Obj_ov003_02238630::func_ov003_0221be34()
{
    int state = func_020b2470(unk_136);
    if (state != 0) {
        int flag;
        if (state == 2) {
            flag = 1;
        } else {
            flag = 0;
        }
        // the ROM rewrites the byte, not the bit
        unsigned char *flags = (unsigned char *) this + 0x236;
        unsigned int v = *flags;
        v &= ~2;
        v |= (flag & 1) << 1;
        *flags = (unsigned char) v;
        func_ov003_0221bfa8(2);
    }
}

int Obj_ov003_02238630::func_ov003_0221bd90()
{
    D t;
    func_0203ee14(this, this);
    func_020a8164(*this, data_ov003_02238778);
    if (vfunc_8c() == 0) {
        unk_1E = 0x34;
        if (!flag_236_1) {
            func_020b23ec(unk_136, 0);
        }
    } else if (flag_236_1) {
        unk_1E = 0x31;
    } else if (func_020ae2c4()) {
        unk_1E = 0x32;
    } else {
        unk_1E = 0;
    }
    ((UnkStruct_0221bd90 *) unk_40)->unk_08 = 1;
    func_02066914(*this, 0);
    return 1;
}

void Obj_ov003_02238630::func_ov003_0221bd6c()
{
    UnkStruct_0221bd6c *b = (UnkStruct_0221bd6c *) unk_40;
    if (b != 0) {
        if (b->unk_04 != 0) {
            func_ov003_0221bfa8(3);
        }
    }
}
