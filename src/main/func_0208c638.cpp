/* func_0208c638 @ 0x0208c638, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_020a7e44(int);

class UnkStruct_0208c638 {
  public:
    virtual void vfunc0();
    virtual void vfunc1();
    virtual int vfunc2();
    char pad_04[0xBC];
    int unk_C0;
};

extern "C" int func_0208c638(UnkStruct_0208c638 *obj)
{
    if (obj->unk_C0 == 2) {
        func_020a7e44(obj->unk_C0);
    }
    return obj->vfunc2();
}
