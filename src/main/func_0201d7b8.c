/* func_0201d7b8 @ 0x0201d7b8, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02014bc0(void *, unsigned int);

typedef struct {
    unsigned char pad_00[0x138];
    unsigned int _field_138;
} UnkStruct_0201d7b8;

int func_0201d7b8(UnkStruct_0201d7b8 *arg)
{
    unsigned int field = arg->_field_138;
    if (field != 0) {
        func_02014bc0(arg, field + 0x74);
        return 1;
    }
    return 0;
}
