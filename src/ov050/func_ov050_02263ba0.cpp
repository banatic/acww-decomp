/* func_ov050_02263ba0 @ 0x02263ba0, 0x44 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

extern struct UnkStruct_02263ba0;
typedef void (UnkStruct_02263ba0::*Pmf)();

struct UnkStruct_02263ba0 {
    char pad_00[0xb8];
    Pmf pmf;
};

extern Pmf __ptmf_null;

extern "C" void func_ov050_02263ba0(UnkStruct_02263ba0 *obj)
{
    if (obj->pmf) {
        (obj->*(obj->pmf))();
        obj->pmf = __ptmf_null;
    }
}
