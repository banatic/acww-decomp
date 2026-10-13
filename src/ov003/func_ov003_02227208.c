/* func_ov003_02227208 @ 0x02227208, 0x64 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *data_ov003_02239ef0[];
extern void **data_ov003_02239f2c[];
extern void *data_ov003_0223cf78;
int func_ov003_02227170(void *self, int k);
int func_02055324(void *p, void *t, void *g);
void *func_020552ec(void *p, void *e);

int func_ov003_02227208(char *self)
{
    void **p;
    int i;
    int r = 0;
    int k = func_ov003_02227170(self, 2);
    if (func_02055324(self + 0x4b00, data_ov003_02239ef0[k], data_ov003_0223cf78) != 0) {
        p = data_ov003_02239f2c[k];
        for (i = 0; i < 5; i++) {
            *(void **) (self + i * 4 + 0x46f4) = func_020552ec(self + 0x4b00, *p);
            p++;
        }
        r = 1;
    }
    return r;
}
