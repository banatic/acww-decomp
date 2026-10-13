/* func_ov094_0229b0e0 @ 0x0229b0e0, 0x18 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov094_0229bf80[];
extern void func_020edb3c(void *);

void *func_ov094_0229b0e0(void *arg)
{
    *(char **) arg = data_ov094_0229bf80;
    func_020edb3c(arg);
    return arg;
}
