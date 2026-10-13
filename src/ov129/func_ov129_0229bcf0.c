/* func_ov129_0229bcf0 @ 0x0229bcf0, 0x2c bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x2f78];
    unsigned short array[16];
} UnkStruct_0229bcf0;

int func_ov129_0229bcf0(UnkStruct_0229bcf0 *s, unsigned short target)
{
    int i;
    for (i = 0; i < 16; i++) {
        if (target == s->array[i]) {
            return i;
        }
    }
    return -1;
}
