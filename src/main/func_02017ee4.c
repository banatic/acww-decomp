/* func_02017ee4 @ 0x02017ee4, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02019de4(void *p, int q);
extern int func_02017f1c(void *p, int q, int r, int s, int t);
extern void func_02019af0(void *p, int q);

void func_02017ee4(void *arg0, int arg1)
{
    int result;
    result = func_02019de4(arg0, arg1);
    if (func_02017f1c(arg0, arg1, result + 0x22, 0x28, 1) != 0) {
        func_02019af0(arg0, 1);
        ((unsigned char *) arg0)[0x98] = 0x14;
    }
}
