/* func_02082f78 @ 0x02082f78, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02082f78 {
  public:
    virtual int f0();
    virtual int f1();
    virtual int f2();
    signed char b;
};

extern "C" int func_02083940(int a, signed char b);

extern "C" int func_02082f78(UnkStruct_02082f78 *p)
{
    int r = p->f2();
    int result = 0;
    if (r != 0) {
        result = func_02083940(r, p->b);
    }
    return result;
}
