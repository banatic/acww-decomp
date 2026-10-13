/* func_ov071_02278a54 @ 0x02278a54, 0x50 bytes, Thumb, module ov071
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov071_02279d04(struct UnkStruct_02278a54_2 *, int);
extern "C" int func_0201c2a4(struct UnkStruct_02278a54_2 *, int);
extern "C" void func_02016108(class UnkStruct_02278a54 *, int);

class UnkStruct_02278a54 {
  public:
    virtual void method0();
    virtual void method1();
    virtual void method2();
};

struct UnkStruct_02278a54_2 {
    char pad_00[0x658];
    UnkStruct_02278a54 sub;
};

extern "C" void func_ov071_02278a54(UnkStruct_02278a54_2 *self, int type)
{
    switch (type) {
        case 0:
            func_ov071_02279d04(self, 0);
            break;
        case 3:
            self->sub.method2();
            func_02016108(&self->sub, func_0201c2a4(self, 4));
            func_ov071_02279d04(self, 5);
            break;
        case 8:
            func_ov071_02279d04(self, 3);
            break;
    }
}
