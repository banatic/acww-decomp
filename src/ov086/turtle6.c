/* turtle6: 2 functions, module ov086
 * mwccarm 1.2/base -O4,s
 * func_ov086_02278a28 @ 0x02278a28, 0x2c bytes, Thumb
 * func_ov086_02278a00 @ 0x02278a00, 0x28 bytes, Thumb
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

void *func_ov086_02278a00(void *p)
{
    *(void **) p = &data_ov086_0227938c;
    func_ov086_02278eb0((char *) p + 0x658);
    func_0202ee5c(p);
    return p;
}
