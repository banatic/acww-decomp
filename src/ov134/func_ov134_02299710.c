/* func_ov134_02299710 @ 0x02299710, 0x22 bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02299710 {
    int unk_00;
    char pad_04[0xa7];
    unsigned char unk_AB;
    unsigned char unk_AC;
};

int func_ov134_02299710(struct UnkStruct_02299710 *obj, int arg)
{
    arg -= obj->unk_AB - obj->unk_00;
    if (arg < 0) {
        arg = 0;
    }
    arg >>= 4;
    if (arg >= obj->unk_AC) {
        arg = obj->unk_AC - 1;
    }
    return arg;
}
