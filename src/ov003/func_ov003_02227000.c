/* func_ov003_02227000 @ 0x02227000, 0x3c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *data_ov003_02239f14[];
int func_ov003_02227170(void *self, int k);
int func_ov003_02227324(void *a, void *b, void *c, void *d, int e);

int func_ov003_02227000(void *a, void *b, void *c)
{
    int k = func_ov003_02227170(a, 2);
    return func_ov003_02227324(a, b, c, data_ov003_02239f14[k], 6) != 0 ? 1 : 0;
}
