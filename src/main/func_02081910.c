/* func_02081910 @ 0x02081910, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02081910 {
    char pad_00[0x7c];
    unsigned short unk_7C;
};

int func_02081910(struct UnkStruct_02081910 *arg)
{
    if ((((unsigned int) arg->unk_7C) << 19) >> 31) {
        return 1;
    } else {
        return 0;
    }
}
