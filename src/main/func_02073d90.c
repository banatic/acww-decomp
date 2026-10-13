/* func_02073d90 @ 0x02073d90, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02073d90 {
    unsigned char pad_00[0x64];
    unsigned int unk_64;
    unsigned char pad_68[4];
    unsigned char unk_6C;
};

extern int func_02073dd4(struct UnkStruct_02073d90 *s, unsigned int value);

int func_02073d90(struct UnkStruct_02073d90 *s)
{
    if (func_02073dd4(s, s->unk_64) != 0) {
        if (s->unk_6C >= 2) {
            return 1;
        }
    }
    return 0;
}
