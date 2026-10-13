/* func_ov045_02260668 @ 0x02260668, 0x48 bytes, Thumb, module ov045
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02260668_2 {
  public:
    virtual void f0() {}
    virtual void f1() {}
    virtual void f2() {}
};

struct UnkStruct_02260668 {
    unsigned char pad_00[0x68c];
    UnkStruct_02260668_2 sub;
};

extern "C" int func_0201c2a4(UnkStruct_02260668 *, int);
extern "C" void func_02016108(UnkStruct_02260668_2 *, int);
extern "C" void func_ov045_02260e50(UnkStruct_02260668 *, int);

extern "C" void func_ov045_02260668(UnkStruct_02260668 *self, int kind)
{
    switch (kind) {
        case 0:
        case 1:
            self->sub.f2();
            {
                int ret = func_0201c2a4(self, 4);
                func_02016108(&self->sub, ret);
            }
            func_ov045_02260e50(self, 1);
            break;
        case 8:
            func_ov045_02260e50(self, 0);
            break;
    }
}
