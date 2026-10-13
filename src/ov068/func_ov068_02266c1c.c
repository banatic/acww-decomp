/* func_ov068_02266c1c @ 0x02266c1c, 0x18 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x14];
    unsigned short count;
} UnkStruct_02266c1c;

void func_ov068_02266c1c(UnkStruct_02266c1c *self)
{
    if (++self->count > 0x960) {
        self->count = 0x960;
    }
}
