/* func_02081c00 @ 0x02081c00, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02081c00 {
    unsigned char pad_00[0x7c];
    unsigned short : 1;
    unsigned short flag : 1;
};

int func_02081c00(struct UnkStruct_02081c00 *s)
{
    if (s->flag == 1) {
        return 1;
    } else {
        return 0;
    }
}
