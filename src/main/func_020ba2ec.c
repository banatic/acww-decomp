/* func_020ba2ec @ 0x020ba2ec, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern void func_02098ff8(int a, int b);
extern void func_020bc514(int *p);
extern int data_021f8b48;

void func_020ba2ec(void)
{
    int ret;
    ret = func_020984e8();
    if (ret) {
        func_02098ff8(ret, 0x32);
        func_020bc514(&data_021f8b48);
    }
}
