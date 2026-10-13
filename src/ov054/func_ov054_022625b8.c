/* func_ov054_022625b8 @ 0x022625b8, 0x14 bytes, Thumb, module ov054
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_ov054_02262df8[];

typedef struct {
    unsigned char pad_00[0x808];
    unsigned int idx;
} Struct_ov054_022625b8;

unsigned int func_ov054_022625b8(Struct_ov054_022625b8 *obj)
{
    return data_ov054_02262df8[obj->idx];
}
