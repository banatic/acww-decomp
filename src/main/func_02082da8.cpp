/* func_02082da8 @ 0x02082da8, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02082da8 {
  public:
    virtual int f1();
    virtual int f2();
    virtual int f3();
    signed char c;
};

extern "C" int func_02083404(int, signed char);

extern "C" int func_02082da8(UnkStruct_02082da8 *obj)
{
    int r = obj->f3();
    int ret = 0;
    if (r != 0) {
        ret = func_02083404(r, obj->c);
    }
    return ret;
}
