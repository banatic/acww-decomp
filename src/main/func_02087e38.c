/* func_02087e38 @ 0x02087e38, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02087e38 {
    unsigned char pad_00[8];
    unsigned char b0 : 1;
};

int func_02087e38(struct UnkStruct_02087e38 *s)
{
    if (s->b0) {
        return 1;
    } else {
        return 0;
    }
}
