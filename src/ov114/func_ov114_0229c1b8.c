/* func_ov114_0229c1b8 @ 0x0229c1b8, 0x2c bytes, Thumb, module ov114
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229c1b8 {
    char pad_00[0x1264];
    unsigned int bits[1];
} UnkStruct_0229c1b8;

int func_ov114_0229c1b8(UnkStruct_0229c1b8 *p, int idx)
{
    int ret = 1;
    int mask = 1 << (idx & 31);
    int word = idx >> 5;
    if (!(mask & p->bits[word])) {
        ret = 0;
    }
    return ret;
}
