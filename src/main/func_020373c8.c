/* func_020373c8 @ 0x020373c8, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020373c8 {
    unsigned char pad_00[6];
    unsigned char unk_06;
    unsigned char pad_07;
    unsigned int unk_08;
};

int func_020373c8(struct UnkStruct_020373c8 *a, unsigned int b, unsigned int c, unsigned int d, unsigned int e)
{
    unsigned int x = a->unk_08 + (unsigned char) a->unk_06 * 60;
    unsigned int start = c + b * 60;
    unsigned int end = e + d * 60;
    int result = 0;
    if (start <= end) {
        if (x >= start && x < end) {
            result = 1;
        }
    } else {
        if (x >= start || x < end) {
            result = 1;
        }
    }
    return result;
}
