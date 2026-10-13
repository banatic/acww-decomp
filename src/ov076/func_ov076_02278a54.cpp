/* func_ov076_02278a54 @ 0x02278a54, 0x58 bytes, Thumb, module ov076
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02278a54 {
  public:
    virtual void v0() = 0;
    virtual void v1() = 0;
    virtual void v2() = 0;
};

extern "C" int func_0201c2a4(void *self, int a);
extern "C" void func_02016108(UnkStruct_02278a54 *inner, int arg);
extern "C" void func_ov076_02279370(void *self, int arg);

extern "C" void func_ov076_02278a54(void *self, int key)
{
    switch (key) {
        case 0:
            ((UnkStruct_02278a54 *) ((char *) self + 0x658))->v2();
            func_02016108((UnkStruct_02278a54 *) ((char *) self + 0x658), func_0201c2a4(self, 4));
            func_ov076_02279370(self, 1);
            break;
        case 8:
            if (*(unsigned char *) ((char *) self + 0x71c) != 0) {
                func_ov076_02279370(self, 4);
            } else {
                func_ov076_02279370(self, 3);
            }
            break;
        default:
            break;
    }
}
