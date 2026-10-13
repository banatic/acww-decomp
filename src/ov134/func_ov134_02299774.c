/* func_ov134_02299774 @ 0x02299774, 0x3a bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02299774 {
    unsigned char pad_00[4];
    int unk_04;
    unsigned char pad_08[0xb0 - 8];
    unsigned char unk_B0;
};

extern int func_ov134_022999ac(struct UnkStruct_02299774 *p);

int func_ov134_02299774(struct UnkStruct_02299774 *obj)
{
    if (obj->unk_B0 > 1) {
        int ret;
        obj->unk_B0--;
        ret = func_ov134_022999ac(obj);
        if (ret < 0x30) {
            obj->unk_04 -= 0x30 - ret;
        }
        return 1;
    }
    return 0;
}
