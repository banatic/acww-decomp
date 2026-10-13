/* func_ov145_02299668 @ 0x02299668, 0x12 bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xb4];
    unsigned short unk_B4;
} UnkStruct_02299668;

int func_ov145_02299668(UnkStruct_02299668 *self, int mask)
{
    if ((self->unk_B4 & mask) != 0) {
        return 1;
    }
    return 0;
}
