/* func_02015da0 @ 0x02015da0, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x4c];
    int unk_4C;
    int unk_50;
} UnkStruct_02015da0;

int func_02015da0(UnkStruct_02015da0 *ptr, int index)
{
    switch (index) {
        case 0:
            return ptr->unk_4C;
        case 1:
            return ptr->unk_50;
        default:
            return 0;
    }
}
