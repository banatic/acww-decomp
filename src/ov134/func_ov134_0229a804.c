/* func_ov134_0229a804 @ 0x0229a804, 0x64 bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229a804 {
    unsigned char pad_00[0xa0];
    unsigned char unk_A0;
    unsigned char pad_A1[0x10];
    unsigned char unk_B1;
};

extern void func_ov134_0229a868(struct UnkStruct_0229a804 *obj, unsigned char val);

void func_ov134_0229a804(struct UnkStruct_0229a804 *obj)
{
    switch (obj->unk_A0) {
        case 0:
        case 1:
            if (obj->unk_B1 < 4u) {
                func_ov134_0229a868(obj, (unsigned char) (obj->unk_B1 + 1));
            } else {
                func_ov134_0229a868(obj, 6);
            }
            break;
        case 2:
        case 3:
            if (obj->unk_B1 < 2u) {
                func_ov134_0229a868(obj, (unsigned char) (obj->unk_B1 + 1));
            } else {
                func_ov134_0229a868(obj, 6);
            }
            break;
        default:
            break;
    }
}
