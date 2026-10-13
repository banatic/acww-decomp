/* func_ov054_02261f78 @ 0x02261f78, 0x20 bytes, Thumb, module ov054
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov054_02263004;
extern void func_0202eb20(void *);
extern void func_020edb3c(void *);
void *func_ov054_02261f78(void *arg)
{
    *(void **) arg = &data_ov054_02263004;
    func_0202eb20(arg);
    func_020edb3c(arg);
    return arg;
}
