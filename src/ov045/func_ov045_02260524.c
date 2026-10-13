/* func_ov045_02260524 @ 0x02260524, 0x80 bytes, Thumb, module ov045
 * mwccarm 1.2/base -O4,s
 */

extern struct Entry {
    unsigned char c;
    unsigned int w;
} data_ov045_022611a8[];
extern struct Entry data_ov045_02261230[];

struct Param {
    char pad_00[0x74c];
    unsigned char c;
    char pad_74D[3];
    unsigned int w;
};

int func_ov045_02260524(struct Param *p)
{
    unsigned char i;
    i = 0;
    while (i < 0x11) {
        if (p->c == data_ov045_022611a8[i].c && p->w == data_ov045_022611a8[i].w) {
            return 1;
        }
        i++;
    }
    i = 0;
    while (i < 0x15) {
        if (p->c == data_ov045_02261230[i].c && p->w == data_ov045_02261230[i].w) {
            return 2;
        }
        i++;
    }
    return 0;
}
