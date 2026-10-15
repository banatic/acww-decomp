/* func_ov004_02233f18 @ 0x02233f18, 0x34 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_02233f4c(char *arg0);
extern int func_0204678c(void);
extern void func_ov004_0223380c(void *);
extern void *data_ov004_02258ae4;
extern char data_ov004_02258af4;

int func_ov004_02233f18(void *a)
{
    int r = 0;
    if (func_ov004_02233f4c((char *) a) != 0) {
        func_0204678c();
        data_ov004_02258ae4 = a;
        func_ov004_0223380c(&data_ov004_02258af4);
        r = 1;
    }
    return r;
}
