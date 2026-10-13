/* func_020e9fd4 @ 0x020e9fd4, 0x70 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

class UnkStruct_020e9fd4 {
  public:
    virtual void vfunc0();
    virtual void vfunc1();
    virtual void vfunc2();
    virtual void vfunc3();
    virtual void vfunc4();
    virtual void vfunc5();
    int unk_04;
    int unk_08;
    int unk_0C;
};

extern "C" void func_020ea0a4(UnkStruct_020e9fd4 *);
extern "C" void func_020ea084(UnkStruct_020e9fd4 *);
extern "C" void func_020e9c48(int, UnkStruct_020e9fd4 *);

extern "C" void func_020e9fd4(UnkStruct_020e9fd4 *obj)
{
    func_020ea0a4(obj);
    obj->vfunc5();
    obj->unk_04 = 0;
    obj->unk_08 = 0;
    func_020ea084(obj);
    int saved = obj->unk_0C;
    obj->vfunc0();
    if (saved == 0) {
        return;
    }
    func_020e9c48(saved, obj);
}
