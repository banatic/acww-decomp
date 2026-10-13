/* func_020bcab0 @ 0x020bcab0, 0xd4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x2f38];
    int a;
    int b;
    int c;
    int d;
    int unk_2F48;
} UnkStruct_020bcab0;

extern int func_020bcdf8(UnkStruct_020bcab0 *s, int i);
extern void func_020bcda0(UnkStruct_020bcab0 *s, int i, int x, int y);
extern int func_020644cc(int n);

void func_020bcab0(UnkStruct_020bcab0 *s)
{
    int *ptrs[4];
    int **p;
    int i;
    int all;

    ptrs[0] = &s->a;
    ptrs[1] = &s->b;
    ptrs[2] = &s->c;
    ptrs[3] = &s->d;
    p = ptrs;
    all = 1;
    for (i = 0; i < 4; i++, p++) {
        int *e = *p;
        if (*e > 0) {
            *e = *e - 1;
            if (*e <= 0) {
                if (func_020bcdf8(s, i) != 0) {
                    func_020bcda0(s, i, 0, 0);
                } else {
                    *e = 1;
                }
            }
        }
        all = all & (*e <= 0 ? 1 : 0);
        if (all != 0) {
            all = 1;
        } else {
            all = 0;
        }
    }
    if (all != 0) {
        int n = func_020644cc(4);
        p = ptrs;
        for (i = 0; i < 4; i++, p++) {
            if (i != n) {
                **p = s->unk_2F48 + func_020644cc(0x1e);
            }
        }
    }
}
