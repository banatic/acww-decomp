/* func_ov003_0221608c @ 0x0221608c, 0x90 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN12Obj_020d82b419func_ov003_0221608cEP12Msg_02007364i
 */

#include "cpp/main/Obj_020d82b4.h"

extern "C" void func_020109fc(Obj_020d82b4 *self, int a, int b, int c);
extern "C" void func_ov003_0221611c(unsigned short *p);
extern "C" int func_02073908(void *a, int b);
extern "C" void func_0203ee14(Base_0203f080 *self, Base_02066994 *recv);
extern "C" void func_020a8164(Base_02066994 &recv, void *name);
extern "C" void func_0203ae98(void);
extern "C" void func_02035624(int);
extern "C" void func_02035684(int, int, int);
extern "C" void func_020356c4(int, int, int, int);

struct S12c {
    char pad_00[8];
    int unk_08;
};

class Scope {
  public:
    Scope() {}
    ~Scope() {}
};

extern unsigned char data_020ccf94[];
extern unsigned char data_ov003_02238134[];

void Obj_020d82b4::func_ov003_0221608c(Msg_02007364 *msg, int prev)
{
    Scope scope;
    func_020109fc(this, 0x48, 3, 0);
    func_ov003_0221611c(&unk_7D4);
    if (func_02073908(*(void **) data_020ccf94, unk_800) != 0) {
        func_0203ee14(this, this);
        func_020a8164(*this, (void *) data_ov003_02238134);
        unk_1E = 0xa;
        ((S12c *) unk_40)->unk_08 = 1;
        func_0203ae98();
        func_02035624(0x12);
        func_02035684(0xc, 0, 1);
        func_020356c4(0xd, 0x42, 0x7f, 1);
    }
}
