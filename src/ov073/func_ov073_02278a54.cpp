/* func_ov073_02278a54 @ 0x02278a54, 0x50 bytes, Thumb, module ov073
 * mwccarm 1.2/base -O4,s
 */

class SubClass {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
};

struct UnkStruct_02278a54 {
    char pad_00[0x658];
    SubClass sub;
};

extern "C" void func_ov073_02279608(UnkStruct_02278a54 *obj, int mode);
extern "C" int func_0201c2a4(UnkStruct_02278a54 *obj, int n);
extern "C" void func_02016108(SubClass *sub, int val);

extern "C" void func_ov073_02278a54(UnkStruct_02278a54 *obj, int mode)
{
    switch (mode) {
        case 0:
            func_ov073_02279608(obj, 0);
            break;
        case 3:
            obj->sub.f2();
            {
                int result = func_0201c2a4(obj, 4);
                func_02016108(&obj->sub, result);
            }
            func_ov073_02279608(obj, 4);
            break;
        case 8:
            func_ov073_02279608(obj, 2);
            break;
    }
}
