/* func_02059c60 @ 0x02059c60, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02059ac4(void *);
extern void func_0200451c(void *ptr);
extern int data_021c9350;

int func_02059c60(int param)
{
    func_02059ac4((void *) param);
    func_0200451c((void *) (param + 0xdc));
    data_021c9350 = param;
    return 1;
}
