/* func_020a8f88 @ 0x020a8f88, 0x2e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_020a8f88 {
  public:
    virtual int v0();
    virtual int v1();
    virtual int v2();
    virtual int v3();
    char pad_04[12];
    int unk_10;
};

extern "C" UnkStruct_020a8f88 *func_020a9034(int a, int b, int c);
extern "C" void func_020a8fb8(UnkStruct_020a8f88 *obj);

extern "C" int func_020a8f88(int arg0)
{
    int result = 0;
    UnkStruct_020a8f88 *obj = func_020a9034(0, 1, 2);
    if (obj) {
        obj->unk_10 = arg0;
        result = obj->v3();
    }
    func_020a8fb8(obj);
    return result;
}
