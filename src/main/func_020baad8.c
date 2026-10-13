/* func_020baad8 @ 0x020baad8, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fea4(void);
extern void func_020bb240(int *p);
extern void func_020bbb6c(int *p, unsigned int *a, unsigned int *b);
extern void func_020bba14(void);
extern int data_021f75b0;

void func_020baad8(void)
{
    unsigned int local1, local2;
    if (func_0206fea4() == 0) {
        func_020bb240(&data_021f75b0);
    }
    func_020bbb6c(&data_021f75b0, &local1, &local2);
    func_020bba14();
}
