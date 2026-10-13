/* func_02082cb8 @ 0x02082cb8, 0x2a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02082cb8 {
  public:
    virtual int m0();
    virtual int m1();
    virtual int m2();
    signed char data;
};

extern "C" int func_02083148(int a, signed char b, int c);

extern "C" int func_02082cb8(UnkStruct_02082cb8 *obj, int arg1)
{
    int ret = obj->m2();
    int res = 0;
    if (ret != 0) {
        res = func_02083148(ret, obj->data, arg1);
    }
    return res;
}
