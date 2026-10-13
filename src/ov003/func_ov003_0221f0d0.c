/* func_ov003_0221f0d0 @ 0x0221f0d0, 0x40 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x20];
    int unk_20;
    char pad_24[4];
} Elem; // sizeof == 0x28
typedef struct {
    Elem *data;
    unsigned int w;
    unsigned int h;
} Tbl;
extern Tbl *data_021c80bc;

int func_ov003_0221f0d0(int a, unsigned int x, unsigned int y)
{
    Tbl *t = data_021c80bc;
    Elem *e;
    if (t != 0) {
        if (x < t->w && y < t->h && t->data != 0) {
            e = &t->data[y * t->w + x];
        } else {
            e = 0;
        }
        if (e != 0) {
            return e->unk_20;
        }
    }
    return 0;
}
