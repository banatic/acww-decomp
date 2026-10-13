/* func_02082c98 @ 0x02082c98, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02082c98 {
    virtual int f1() = 0;
    virtual int f2() = 0;
    virtual int f3() = 0;
    char b;
};

extern "C" int func_02083110(int a, int b);

extern "C" int func_02082c98(UnkStruct_02082c98 *p)
{
    int result = p->f3();
    if (result) {
        return func_02083110(result, p->b);
    } else {
        return 0;
    }
}
