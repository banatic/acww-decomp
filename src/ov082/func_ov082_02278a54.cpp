/* func_ov082_02278a54 @ 0x02278a54, 0x44 bytes, Thumb, module ov082
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02278a54 {
  public:
    virtual void m0();
    virtual void m1();
    virtual void m2();
};

struct Parent {
    unsigned char pad_00[0x658];
    UnkStruct_02278a54 sub;
};

extern "C" {
int func_0201c2a4(Parent *self, int a);
void func_02016108(UnkStruct_02278a54 *sub, int v);
void func_ov082_02279324(Parent *self, int x);
}

extern "C" void func_ov082_02278a54(Parent *self, int mode)
{
    switch (mode) {
        case 0:
            self->sub.m2();
            {
                int v = func_0201c2a4(self, 4);
                func_02016108(&self->sub, v);
            }
            func_ov082_02279324(self, 1);
            break;
        case 8:
            func_ov082_02279324(self, 0);
            // fall through
        default:
            break;
    }
}
