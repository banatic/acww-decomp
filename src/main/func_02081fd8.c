/* func_02081fd8 @ 0x02081fd8, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020e18ec;
extern void func_020a887c(void *ptr);

void *func_02081fd8(void *arg0)
{
    *(char **) arg0 = &data_020e18ec;
    func_020a887c(arg0);
    return arg0;
}
