/* func_0206e63c @ 0x0206e63c, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a6c04(void);
extern void func_02074330(void *);
extern void func_02054070(void);
extern int data_021fbdd0;

void func_0206e63c(void *arg)
{
    if (arg == 0) {
        func_020a6c04();
    }
    func_02074330(arg);
    func_02054070();
    data_021fbdd0++;
    *(volatile unsigned int *) 0x04000540 = 3;
}
