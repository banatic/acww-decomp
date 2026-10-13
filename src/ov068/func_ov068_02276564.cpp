/* func_ov068_02276564 @ 0x02276564, 0x34 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

class FuncOv068Class {
  public:
    char pad_00[0xa44];
    int (FuncOv068Class::*pmf)();
};

extern "C" int func_ov068_02276564(FuncOv068Class *obj)
{
    if (obj->pmf) {
        return (obj->*obj->pmf)();
    }
    return 1;
}
