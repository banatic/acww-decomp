/* func_ov079_02278a54 @ 0x02278a54, 0x50 bytes, Thumb, module ov079
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov079_02279c34(void *self, int n);
extern "C" int func_0201c2a4(void *self, int n);
extern "C" void func_02016108(void *obj, int value);

class UnkStruct_02278a54 {
  public:
    virtual void vfunc_00();
    virtual void vfunc_04();
    virtual void vfunc_08();
};

extern "C" void func_ov079_02278a54(void *self, int type)
{
    switch (type) {
        case 0:
            func_ov079_02279c34(self, 0);
            break;
        case 3:
            ((UnkStruct_02278a54 *) ((char *) self + 0x658))->vfunc_08();
            {
                int val = func_0201c2a4(self, 4);
                func_02016108((UnkStruct_02278a54 *) ((char *) self + 0x658), val);
            }
            func_ov079_02279c34(self, 4);
            break;
        case 8:
            func_ov079_02279c34(self, 2);
            break;
        default:
            break;
    }
}
