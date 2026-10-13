/* func_ov071_02279c54 @ 0x02279c54, 0xb0 bytes, Thumb, module ov071
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
} UnkStruct_02279c54;

int func_ov071_02279c54(int unused, UnkStruct_02279c54 *a, UnkStruct_02279c54 *b, int mode)
{
    int ret, c2, c1;

    if (mode == 0) {
        ret = 0;
        c2 = 0;
        c1 = 0;
        if (b->unk_00 > a->unk_00 - 0x8000) {
            if (b->unk_00 < a->unk_00 + 0x8000) {
                c1 = 1;
            }
        }
        if (c1 != 0) {
            if (b->unk_08 > a->unk_08 - 0xc000) {
                c2 = 1;
            }
        }
        if (c2 != 0) {
            if (b->unk_08 < a->unk_08 + 0x6000) {
                ret = 1;
            }
        }
    } else {
        ret = 0;
        c2 = 0;
        c1 = 0;
        if (b->unk_00 > a->unk_00 - 0x10000) {
            if (b->unk_00 < a->unk_00 + 0x10000) {
                c1 = 1;
            }
        }
        if (c1 != 0) {
            if (b->unk_08 > a->unk_08 - 0x1a000) {
                c2 = 1;
            }
        }
        if (c2 != 0) {
            if (b->unk_08 < a->unk_08 + 0xa000) {
                ret = 1;
            }
        }
    }
    return ret;
}
