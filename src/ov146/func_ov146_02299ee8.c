/* func_ov146_02299ee8 @ 0x02299ee8, 0x1e bytes, Thumb, module ov146
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char unk_00;
    unsigned char unk_01;
    unsigned char pad_02[30];
    unsigned char unk_20;
} UnkStruct_02299ee8;

int func_ov146_02299ee8(int unused, UnkStruct_02299ee8 *ptr)
{
    if (ptr->unk_20 == 6 && (ptr->unk_00 != 0 || ptr->unk_01 != 0)) {
        return 1;
    }
    return 0;
}
