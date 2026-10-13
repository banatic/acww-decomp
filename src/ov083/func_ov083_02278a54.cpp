/* func_ov083_02278a54 @ 0x02278a54, 0x44 bytes, Thumb, module ov083
 * mwccarm 1.2/base -O4,s
 */

extern "C" {
class UnkStruct_02278a54 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
};
struct UnkStruct_02278a54_2 {
    char pad_00[0x65c];
    UnkStruct_02278a54 sub;
};
int func_0201c2a4(UnkStruct_02278a54_2 *self, int a);
void func_02016108(UnkStruct_02278a54 *sub, int a);
void func_ov083_02278e98(UnkStruct_02278a54_2 *self, int a);
void func_ov083_02278a54(UnkStruct_02278a54_2 *self, int arg)
{
    switch (arg) {
        case 0:
            self->sub.f2();
            func_02016108(&self->sub, func_0201c2a4(self, 4));
            func_ov083_02278e98(self, 1);
            break;
        case 8:
            func_ov083_02278e98(self, 0);
            break;
    }
}
}
