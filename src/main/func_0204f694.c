/* func_0204f694 @ 0x0204f694, 0x6e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int w;
    unsigned int h;
} Dim;
typedef struct {
    void *data;
    Dim dim;
} SInfo;

extern int func_02037d64(void *cell, void *arg);

void *func_0204f694(SInfo *s, void *arg)
{
    int x, y;
    int w, h;
    int x0;
    void *nullp;
    void *c;
    Dim *dp;

    dp = &s->dim;
    w = dp->w;
    h = dp->h;
    x0 = 0;
    nullp = 0;
    for (y = 0; y < h; y++) {
        for (x = x0; x < w; x++) {
            if ((unsigned int) x < s->dim.w && (unsigned int) y < s->dim.h && s->data != 0) {
                c = (char *) s->data + (x + y * s->dim.w) * 0x28;
            } else {
                c = nullp;
            }
            if (c != 0) {
                if (func_02037d64(c, arg) != 0) {
                    return c;
                }
            }
        }
    }
    return 0;
}
