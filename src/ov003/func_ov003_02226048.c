/* func_ov003_02226048 @ 0x02226048, 0x4c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *data_ov003_0223cf70;
extern void *data_021fbe94;
int func_ov003_02226108(void *g, int *a, int *b);
int func_ov003_02226094(void *g, int a);
void func_020e993c(void *p, int q);

int func_ov003_02226048(void)
{
    int r = 0;
    int a = 0;
    int b = 0;
    if (func_ov003_02226108(data_ov003_0223cf70, &a, &b) != 0) {
        if (func_ov003_02226094(data_ov003_0223cf70, a) != 0) {
            r = 1;
        }
    }
    if (b != 0) {
        func_020e993c(data_021fbe94, b);
    }
    return r;
}
