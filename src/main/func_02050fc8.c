/* func_02050fc8 @ 0x02050fc8, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x68];
    unsigned int count;
} UnkStruct_02050fc8;

extern unsigned char data_021c8344[];
extern int func_02050ea8(UnkStruct_02050fc8 *s);

void func_02050fc8(UnkStruct_02050fc8 *s, unsigned int start)
{
    unsigned int i;
    unsigned int row, col;
    unsigned char *p;
    int hi, v;
    v = func_02050ea8(s);
    hi = v << 4;

    for (i = start; i < s->count; i++) {
        row = i >> 3;
        col = ((i - (row << 3)) + 0x30) >> 1;
        if (row < 0x20) {
            p = data_021c8344 + (row << 5) + col;
            if ((i & 1) != 0) {
                *p &= ~0xf0;
                *p |= (unsigned char) hi;
            } else {
                *p &= ~0x0f;
                *p |= (unsigned char) v;
            }
        }
    }
}
