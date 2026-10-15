/* func_ov114_0229d130 @ 0x0229d130, 0x18 bytes, Thumb, module ov114
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020a8c38(void *);
extern char data_ov114_0229daf0[];

void *func_ov114_0229d130(void *arg)
{
    *(void **) arg = data_ov114_0229daf0;
    func_020a8c38(arg);
    return arg;
}
