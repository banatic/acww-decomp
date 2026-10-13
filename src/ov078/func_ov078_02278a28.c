/* func_ov078_02278a28 @ 0x02278a28, 0x2c bytes, Thumb, module ov078
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov078_02279b2c;
extern void func_ov078_02278fe4(void *);
extern void func_0202ee5c(void *);
extern void func_020edf54(void *);

void *func_ov078_02278a28(void *arg)
{
    *(void **) arg = &data_ov078_02279b2c;
    func_ov078_02278fe4((char *) arg + 0x658);
    func_0202ee5c(arg);
    func_020edf54(arg);
    return arg;
}
