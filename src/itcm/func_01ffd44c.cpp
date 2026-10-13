/* func_01ffd44c @ 0x01ffd44c, 0xc0 bytes, ARM, module itcm
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_01ffd44c {
  public:
    virtual int vf0();
};

typedef int (UnkStruct_01ffd44c::*Fn0)();
typedef void (UnkStruct_01ffd44c::*Fn1)(int);

extern "C" int func_01ffd44c(UnkStruct_01ffd44c *obj, Fn0 a, Fn0 b, Fn1 c)
{
    int r;
    int code;

    r = (obj->*b)();
    if (r != 0) {
        r = (obj->*a)();
        if (r == -1) {
            code = 3;
        } else if (r == 1) {
            code = 2;
        } else {
            code = 1;
        }
    } else {
        code = 0;
    }
    (obj->*c)(code);
    return r;
}
