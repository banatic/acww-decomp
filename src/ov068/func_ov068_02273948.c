/* func_ov068_02273948 @ 0x02273948, 0x2c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov068_02277e50;
extern void *func_ov068_022746fc(void *arg);
extern void *func_0202ee5c(void *arg);
extern void func_020edf54(void *arg);

void *func_ov068_02273948(void *arg)
{
    char *p = (char *) arg;
    *(void **) p = (void *) &data_ov068_02277e50;
    func_ov068_022746fc((void *) (p + 0x65c));
    func_0202ee5c(arg);
    func_020edf54(arg);
    return arg;
}
