/* func_ov095_0229cda4 @ 0x0229cda4, 0x38 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229cda4 {
    char pad_00[0x28];
    int unk_28;
};

int func_ov095_0229cda4(struct UnkStruct_0229cda4 *p, int id)
{
    if (id == -1) {
        id = p->unk_28;
    }
    switch (id - 0x104) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            return 1;
        default:
            return 0;
    }
}
