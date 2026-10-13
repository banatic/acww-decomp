/* func_ov003_02226e30 @ 0x02226e30, 0x48 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *data_ov003_0223cf74;
int func_ov003_02227118(void *self, int k);
int func_020555a4(void *p, int k, void *g, int d, int e, int f, int h);

int func_ov003_02226e30(char *self, int *b, int *c, int d)
{
    int r = 1;
    int k = func_ov003_02227118(self, 0);
    if (func_020555a4(self + 0xc6c, k, data_ov003_0223cf74, *b, *c, d, r) == 0) {
        r = 0;
    }
    return r;
}
