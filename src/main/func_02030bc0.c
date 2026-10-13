/* func_02030bc0 @ 0x02030bc0, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int x;
    unsigned int y;
} Pair;

struct UnkStruct_02030bc0 {
    Pair cells[6][6];
    unsigned int pad_120;
    unsigned int width;
    unsigned int height;
    unsigned int pad_12C;
    unsigned int pad_130;
    unsigned int pad_134;
};

extern struct UnkStruct_02030bc0 data_021c31ec[];

void func_02030bc0(int idx)
{
    struct UnkStruct_02030bc0 *d;
    int row, col;
    Pair *fallback;
    Pair *p;

    fallback = 0;
    d = &data_021c31ec[idx];

    for (row = 0; row < d->height; row++) {
        for (col = 0; col < d->width; col++) {
            if (col >= 0 && row >= 0 && col < d->width && row < d->height) {
                p = &d->cells[row][col];
            } else {
                p = fallback;
            }
            if (p) {
                p->x = 0;
                p->y = 0;
            }
        }
    }
}
