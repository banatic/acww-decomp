/* pool_link_2: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02082cb8 @ 0x02082cb8, 0x2a bytes, Thumb
 * func_02082c98 @ 0x02082c98, 0x20 bytes, Thumb
 */

class UnkStruct_02082cb8 {
  public:
    virtual int m0();
    virtual int m1();
    virtual int m2();
    signed char data;
};

extern "C" int func_02083148(int a, signed char b, int c);

struct UnkStruct_02082c98 {
    virtual int f1() = 0;
    virtual int f2() = 0;
    virtual int f3() = 0;
    char b;
};

extern "C" int func_02083110(int a, int b);

extern "C" int func_02082cb8(UnkStruct_02082cb8 *obj, int arg1)
{
    int ret = obj->m2();
    int res = 0;
    if (ret != 0) {
        res = func_02083148(ret, obj->data, arg1);
    }
    return res;
}

extern "C" int func_02082c98(UnkStruct_02082c98 *p)
{
    int result = p->f3();
    if (result) {
        return func_02083110(result, p->b);
    } else {
        return 0;
    }
}
