/* func_ov086_02278a28 @ 0x02278a28, 0x2c bytes, Thumb, module ov086
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov086_0227938c;
extern void *func_ov086_02278eb0(void *);
extern void *func_0202ee5c(void *);
extern void func_020edf54(void *);

void *func_ov086_02278a28(void *arg)
{
    *(void **) arg = (void *) &data_ov086_0227938c;
    func_ov086_02278eb0((char *) arg + 0x658);
    func_0202ee5c(arg);
    func_020edf54(arg);
    return arg;
}
