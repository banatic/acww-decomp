/* func_020ae514 @ 0x020ae514, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020ae514 {
    char pad_00[4];
    signed char unk_04;
    unsigned char unk_05;
};

void func_020ae514(struct UnkStruct_020ae514 *obj, int param)
{
    if (obj->unk_04 != -1) {
        obj->unk_05 |= (1 << (param & 3));
    }
}
