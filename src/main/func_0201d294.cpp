/* func_0201d294 @ 0x0201d294, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0201d294 {
    char pad_00[0x18c];
    int (UnkStruct_0201d294::*pmf)();
};

extern "C" int func_0201d294(UnkStruct_0201d294 *obj)
{
    if (obj->pmf) {
        return (obj->*obj->pmf)();
    } else {
        return 0;
    }
}
