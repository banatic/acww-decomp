/* func_0203a344 @ 0x0203a344, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020da6dc;
extern unsigned char data_020da5f8;
extern void func_02051ad8();

void *func_0203a344(void *arg)
{
    *(unsigned char *volatile *) arg = &data_020da6dc;
    *(unsigned char *volatile *) arg = &data_020da5f8;
    func_02051ad8(arg);
    return arg;
}
