/* func_020a8910 @ 0x020a8910, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_020a8910 {
  public:
    virtual int vfunc0();
    virtual int vfunc1();
    virtual int vfunc2();
    virtual int vfunc3();
    int unk_04;
};

extern "C" void MI_CpuCopy8(int a, int b, int c);

extern "C" int func_020a8910(UnkStruct_020a8910 *obj, int x, int y)
{
    int v3 = obj->vfunc3();
    int v2 = obj->vfunc2();
    int field = obj->unk_04;
    int sum = v3 + field;
    int diff = v2 - field;
    int val = y - x;
    int r4;
    if (!((unsigned) (val + 1) > (unsigned) diff)) {
        r4 = 1;
    } else {
        r4 = 0;
    }
    if (r4 == 0) {
        val = diff - 1;
    }
    MI_CpuCopy8(x, sum, val);
    obj->unk_04 += val;
    return r4;
}
