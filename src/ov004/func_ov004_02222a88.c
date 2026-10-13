/* func_ov004_02222a88 @ 0x02222a88, 0x48 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020edf70(int size);
extern void func_0202e8e4(void *p);
extern void func_0202decc(void *p);
extern void func_02084f88(void *p);
extern int data_ov004_022541d8;
extern int data_ov004_02254148;

void *func_ov004_02222a88(void)
{
    char *p = (char *) func_020edf70(0xa94);
    if (p != 0) {
        func_0202e8e4(p);
        *(int *) p = (int) &data_ov004_022541d8;
        func_0202decc(p + 0x8a0);
        *(int *) (p + 0x8a0) = (int) &data_ov004_02254148;
        func_02084f88(p + 0xa54);
    }
    return p;
}
