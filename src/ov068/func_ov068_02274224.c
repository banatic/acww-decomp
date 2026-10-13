/* func_ov068_02274224 @ 0x02274224, 0x14 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02274224 {
    char pad_00[0xb4];
    unsigned char *data;
};

void func_ov068_02274224(struct UnkStruct_02274224 *self, int flag)
{
    if (flag == 0) {
        self->data[0x74a] = 1;
    }
}
