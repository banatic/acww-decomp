/* func_020c26b4 @ 0x020c26b4, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef int (*Fn)(void *self);

typedef struct {
    union {
        int ofs;
        Fn fn;
    } u;
    int adj;
    int pad_08[2];
} Pmf;

extern Pmf data_021fbbfc[];
extern void func_0209129c(int h);

void func_020c26b4(void *self, int i)
{
    int ok;
    Pmf *e;
    int adj;
    char *t;
    Fn f;

    ok = 1;
    e = &data_021fbbfc[i];
    if (e->u.ofs != 0) {
        adj = e->adj;
        t = (char *) self + (adj >> 1);
        if (adj & 1) {
            f = *(Fn *) (*(char **) t + e->u.ofs);
        } else {
            f = e->u.fn;
        }
        ok = f(t);
    }
    if (ok) {
        if (i != 1 && *(int *) ((char *) self + 0x724) != -1) {
            func_0209129c(*(int *) ((char *) self + 0x724));
            *(int *) ((char *) self + 0x724) = -1;
        }
        *(int *) ((char *) self + 0x654) = i;
    }
}
