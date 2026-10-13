/* func_0201d2fc @ 0x0201d2fc, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Class {
    char pad_00[0x17c];
    int (Class::*pmf)();
};

extern "C" int func_0201d2fc(Class *obj)
{
    if (obj->pmf) {
        return (obj->*obj->pmf)();
    }
    return 0;
}
