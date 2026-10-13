/* func_02089cc0 @ 0x02089cc0, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02089cc0 {
    unsigned char pad_00[0x28];
    unsigned int unk_28;
    unsigned char pad_2C[0x10];
    unsigned char unk_3C;
} UnkStruct_02089cc0;

int func_02089cc0(UnkStruct_02089cc0 *p, unsigned int mask)
{
    if (p->unk_3C != 0) {
        if ((p->unk_28 & mask) != 0) {
            return 1;
        }
        return 0;
    }
    return 0;
}
