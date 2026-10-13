/* func_ov004_022228c0 @ 0x022228c0, 0x34 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

class FuncOv068Class {
  public:
    char pad_00[0xa4c];
    int (FuncOv068Class::*pmf)();
};

extern "C" int func_ov004_022228c0(FuncOv068Class *obj)
{
    if (obj->pmf) {
        return (obj->*obj->pmf)();
    }
    return 1;
}
