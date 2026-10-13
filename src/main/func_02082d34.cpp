/* func_02082d34 @ 0x02082d34, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" int func_020832c4(int a, int b);

class UnkStruct_02082d34 {
  public:
    virtual void vfunc0();
    virtual void vfunc1();
    virtual int vfunc2();
    signed char unk_04;
};

extern "C" int func_02082d34(UnkStruct_02082d34 *obj)
{
    int vr;
    int result;
    vr = obj->vfunc2();
    result = 0;
    if (vr) {
        result = func_020832c4(vr, obj->unk_04);
    }
    return result;
}
