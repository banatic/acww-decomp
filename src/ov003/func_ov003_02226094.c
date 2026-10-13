/* func_ov003_02226094 @ 0x02226094, 0x74 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *data_ov003_02239c88;
extern void *data_ov003_0223cf74;
extern int data_ov003_02237284;
extern int func_ov003_022261f8(char *self);
extern int func_020555a4(void *rec, void *g1, void *g2, int k, void *y, void *p, int q);

int func_ov003_02226094(char *self, void *b)
{
    int t;
    t = func_ov003_022261f8(self);
    if (func_020555a4(self + 0x4840, data_ov003_02239c88, data_ov003_0223cf74, 0, b, &t, 1) == 0) {
        return 0;
    }
    if (func_020555a4(self + 0x48dc, data_ov003_02239c88, data_ov003_0223cf74, 0, b, &data_ov003_02237284, 1)) {
        return 1;
    }
    return 0;
}
