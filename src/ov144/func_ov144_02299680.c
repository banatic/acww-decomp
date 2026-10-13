/* func_ov144_02299680 @ 0x02299680, 0x12 bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xb4];
    unsigned short unk_B4;
} UnkStruct_02299680;
int func_ov144_02299680(UnkStruct_02299680 *p, unsigned short mask)
{
    if (p->unk_B4 & mask) {
        return 1;
    }
    return 0;
}
