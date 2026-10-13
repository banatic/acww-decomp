/* func_02082f04 @ 0x02082f04, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" int func_02083800(int, int);

class UnkStruct_02082f04 {
  public:
    virtual int vf0() = 0;
    virtual int vf1() = 0;
    virtual int vf2() = 0;
    signed char unk_04;
};

extern "C" int func_02082f04(UnkStruct_02082f04 *obj)
{
    int r = obj->vf2();
    int ret = 0;
    if (r != 0) {
        ret = func_02083800(r, obj->unk_04);
    }
    return ret;
}
