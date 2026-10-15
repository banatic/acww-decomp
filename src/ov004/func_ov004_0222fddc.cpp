/* func_ov004_0222fddc @ 0x0222fddc, 0x5c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0222fddc {
    virtual void vfunc_00();
    virtual void vfunc_04();
    virtual void vfunc_08();
    virtual void vfunc_0c();
    virtual void vfunc_10();
    virtual void vfunc_14();
    virtual void vfunc_18();
    virtual void vfunc_1c();
    virtual void vfunc_20();
    virtual void vfunc_24();
    virtual void vfunc_28();
    virtual void vfunc_2c();
    virtual void vfunc_30();
    virtual void vfunc_34();
    virtual void vfunc_38();
    virtual void vfunc_3c();
    virtual void vfunc_40();
    virtual void vfunc_44();
    virtual void vfunc_48();
    virtual void vfunc_4c();
    virtual void vfunc_50();
    virtual void vfunc_54();
    virtual void vfunc_58();
    virtual void vfunc_5c();
    virtual void vfunc_60(int);
};
extern "C" int func_020643dc(int, int, int, int, int);

extern "C" void func_ov004_0222fddc(char *self)
{
    int r = 0x1000 - func_020643dc(*(int *) (self + 0x43c), 0, 0x28000, 0xa000, 0xa000);
    *(int *) (self + 0x198) = r;
    *(int *) (self + 0x428) = r;
    *(int *) (self + 0x43c) += 0x1000;
    if (r == 0) {
        ((UnkStruct_0222fddc *) self)->vfunc_60(0);
    }
}
