/* func_020819bc @ 0x020819bc, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020819bc {
    unsigned char pad_00[0x7c];
    unsigned short : 6;
    unsigned short flag : 1;
};

int func_020819bc(struct UnkStruct_020819bc *s)
{
    if (s->flag) {
        return 1;
    } else {
        return 0;
    }
}
