/* func_ov004_0221d244 @ 0x0221d244, 0x34 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

class FuncOv068Class {
  public:
    char pad_00[0xa48];
    int (FuncOv068Class::*pmf)();
};

extern "C" int func_ov004_0221d244(FuncOv068Class *obj)
{
    if (obj->pmf) {
        return (obj->*obj->pmf)();
    }
    return 1;
}
