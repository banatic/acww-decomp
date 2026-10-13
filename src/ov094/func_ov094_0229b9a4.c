/* func_ov094_0229b9a4 @ 0x0229b9a4, 0x10 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229b9a4 {
    unsigned char pad_00[0x24];
    unsigned char flag;
} UnkStruct_0229b9a4;

int func_ov094_0229b9a4(UnkStruct_0229b9a4 *self, unsigned char value)
{
    if (value == self->flag) {
        return 1;
    } else {
        return 0;
    }
}
