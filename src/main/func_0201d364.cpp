/* func_0201d364 @ 0x0201d364, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class Class {
  public:
    char pad_00[0x16C];
    int (Class::*pmf)();
};

extern "C" int func_0201d364(Class *obj)
{
    if (obj->pmf != 0) {
        return (obj->*obj->pmf)();
    } else {
        return 0;
    }
}
