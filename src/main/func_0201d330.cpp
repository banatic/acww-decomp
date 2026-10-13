/* func_0201d330 @ 0x0201d330, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Class {
    char pad_00[0x174];
    int (Class::*pmf)();
};
extern "C" int func_0201d330(Class *obj)
{
    if (obj->pmf == 0) {
        goto ret0;
    }
    return (obj->*obj->pmf)();
ret0:
    return 0;
}
