/* func_ov114_0229c1a0 @ 0x0229c1a0, 0x18 bytes, Thumb, module ov114
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x12ac];
    unsigned short unk_12AC;
} func_ov114_0229c1a0_struct;

int func_ov114_0229c1a0(func_ov114_0229c1a0_struct *ptr, unsigned short mask)
{
    if ((ptr->unk_12AC & mask) != 0) {
        return 1;
    }
    return 0;
}
