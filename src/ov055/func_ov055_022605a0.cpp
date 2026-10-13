/* func_ov055_022605a0 @ 0x022605a0, 0x70 bytes, Thumb, module ov055
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_02016108(void *p, int v);
extern "C" int func_0201c2a4(void *p, int n);
extern "C" void func_ov055_02260b24(void *p, int mode);

class UnkStruct_022605a0 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
};

class UnkStruct_022605a0_2 {
  public:
    char pad_00[0x658];
    UnkStruct_022605a0 sub;
};

extern "C" void func_ov055_022605a0(UnkStruct_022605a0_2 *obj, int mode)
{
    switch (mode) {
        case 0:
            obj->sub.f2();
            func_02016108(&obj->sub, func_0201c2a4(obj, 4));
            func_ov055_02260b24(obj, 1);
            break;
        case 1:
            obj->sub.f2();
            func_02016108(&obj->sub, func_0201c2a4(obj, 4));
            func_ov055_02260b24(obj, 1);
            break;
        case 8:
            func_ov055_02260b24(obj, 0);
            break;
    }
}
