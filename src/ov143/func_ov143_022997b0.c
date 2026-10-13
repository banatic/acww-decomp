/* func_ov143_022997b0 @ 0x022997b0, 0x28 bytes, Thumb, module ov143
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char v[16];
} Blk16;

extern Blk16 data_ov143_0229afd0;

unsigned char func_ov143_022997b0(int unused, int index)
{
    Blk16 buf;

    buf = data_ov143_0229afd0;
    return buf.v[index];
}
