/* func_ov119_0229a420 @ 0x0229a420, 0x12 bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229a420 {
    char pad_00[0x98];
    unsigned short unk_98;
};

int func_ov119_0229a420(struct UnkStruct_0229a420 *obj, unsigned int mask)
{
    if ((obj->unk_98 & mask) != 0) {
        return 1;
    }
    return 0;
}
