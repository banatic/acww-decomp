/* func_020485d4 @ 0x020485d4, 0x78 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x;
    int y;
} Result;
typedef struct {
    char pad_00[0x20];
    int unk_20;
} Cell;

extern int func_020644cc(int);
extern unsigned char data_021c79e4[8];
extern Cell data_021c7a08[][4];

void func_020485d4(Result *out, int unused, int w, int h)
{
    int k, i, j;
    int total = w * h - data_021c79e4[4];
    if (total > 0) {
        k = func_020644cc(total);
        for (j = 0; j < h; j++) {
            for (i = 0; i < w; i++) {
                Cell *c = (Cell *) ((char *) data_021c7a08 + i * 0x90 + j * 0x24);
                if (((c->unk_20 << 30) >> 31) == 0) {
                    if (k == 0) {
                        out->x = i;
                        out->y = j;
                        return;
                    }
                    k--;
                }
            }
        }
    }
    out->x = -1;
    out->y = -1;
}
