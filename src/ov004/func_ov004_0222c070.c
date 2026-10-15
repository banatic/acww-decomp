/* func_ov004_0222c070 @ 0x0222c070, 0x46 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02096718(int a);
extern int func_ov004_02228850(void *p, int a, int b);
extern int func_ov004_02228b14(void *p, int a, int b);
extern int func_ov004_02228be0(void *p, int a, int b);

int func_ov004_0222c070(int k)
{
    void *p = func_02096718(4);
    if (p != 0) {
        switch (k) {
            case 0:
                func_ov004_02228850(p, 6, -1);
                break;
            case 1:
                func_ov004_02228b14(p, 6, -1);
                break;
            case 2:
                func_ov004_02228be0(p, 6, -1);
                break;
        }
    }
    return 0;
}
