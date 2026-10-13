/* func_ov075_02278a54 @ 0x02278a54, 0x6c bytes, Thumb, module ov075
 * mwccarm 1.2/base -O4,s
 */

extern "C" int func_0201c2a4(void *p, int a);
extern "C" void func_02016108(void *p, int a);
extern "C" void func_ov075_022794b8(void *p, int a);

class UnkStruct_02278a54 {
  public:
    virtual void m0();
    virtual void m1();
    virtual void m2();
};

struct UnkStruct_02278a54_2 {
    char pad_00[0x658];
    UnkStruct_02278a54 sub;
    char pad1[0x718 - 0x658 - sizeof(UnkStruct_02278a54)];
    unsigned char flag;
};

extern "C" void func_ov075_02278a54(UnkStruct_02278a54_2 *obj, int mode)
{
    switch (mode) {
        case 0:
            func_ov075_022794b8(obj, 2);
            break;
        case 3:
            obj->sub.m2();
            {
                int x = func_0201c2a4(obj, 4);
                func_02016108(&obj->sub, x);
            }
            if (obj->flag) {
                func_ov075_022794b8(obj, 1);
            }
            break;
        case 8:
            if (obj->flag == 0) {
                func_ov075_022794b8(obj, 0);
            } else {
                func_ov075_022794b8(obj, 5);
            }
            break;
        default:
            break;
    }
}
