/* func_ov004_0222f320 @ 0x0222f320, 0x14 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char b[16];
} UnkStruct_0222f320;
extern UnkStruct_0222f320 data_ov004_022478a8[];
UnkStruct_0222f320 *func_ov004_0222f320(unsigned int i)
{
    if (i < 2) {
        return &data_ov004_022478a8[i];
    }
    return data_ov004_022478a8;
}
