/* func_ov003_022199d8 @ 0x022199d8, 0x3c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02096718(int);
extern int func_ov003_0220f3d8(void *, int, int);
extern int func_ov003_0220f344(void *, int, int);

int func_ov003_022199d8(int a)
{
    void *x = func_02096718(4);
    if (x != 0) {
        switch (a) {
            case 1:
                return func_ov003_0220f3d8(x, 6, -1);
            case 2:
                return func_ov003_0220f344(x, 6, -1);
        }
        return 0;
    }
    return 0;
}
