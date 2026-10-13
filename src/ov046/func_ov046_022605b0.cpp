/* func_ov046_022605b0 @ 0x022605b0, 0x48 bytes, Thumb, module ov046
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_022605b0 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
};

struct UnkStruct_022605b0_2 {
    char pad_00[0x658];
    UnkStruct_022605b0 sub;
};

extern "C" {
int func_0201c2a4(void *obj, int x);
void func_02016108(UnkStruct_022605b0 *sub, int x);
void func_ov046_022619cc(void *obj, int x);
}

extern "C" void func_ov046_022605b0(UnkStruct_022605b0_2 *obj, int arg1)
{
    switch (arg1) {
        case 0:
        case 1:
            obj->sub.f2();
            func_02016108(&obj->sub, func_0201c2a4(obj, 4));
            func_ov046_022619cc(obj, 3);
            break;
        case 8:
            func_ov046_022619cc(obj, 1);
            break;
        default:
            return;
    }
    return;
}
