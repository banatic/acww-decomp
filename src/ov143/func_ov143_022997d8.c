/* func_ov143_022997d8 @ 0x022997d8, 0x28 bytes, Thumb, module ov143
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char v[16];
} Blk16;

extern Blk16 data_ov143_0229afb0;

unsigned char func_ov143_022997d8(int unused, int index)
{
    Blk16 buf;

    buf = data_ov143_0229afb0;
    return buf.v[index];
}
