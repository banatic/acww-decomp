/* post_clerk_talk_8: 3 functions, module ov054
 * mwccarm 1.2/base -O4,s
 * func_ov054_02261fb0 @ 0x02261fb0, 0x18 bytes, Thumb
 * func_ov054_02261f98 @ 0x02261f98, 0x18 bytes, Thumb
 * func_ov054_02261f78 @ 0x02261f78, 0x20 bytes, Thumb
 */

extern void *func_0202eb70(void *);
extern char data_ov054_02263004[];
extern void *func_0202eb20(void *obj);
extern void func_020edb3c(void *);

void *func_ov054_02261fb0(void *p)
{
    func_0202eb70(p);
    *(unsigned int *) p = (unsigned int) data_ov054_02263004;
    return p;
}

void *func_ov054_02261f98(void *obj)
{
    void *val = ((char *) data_ov054_02263004);

    *(void **) obj = val;
    func_0202eb20(obj);
    return obj;
}

void *func_ov054_02261f78(void *arg)
{
    *(void **) arg = ((char *) data_ov054_02263004);
    func_0202eb20(arg);
    func_020edb3c(arg);
    return arg;
}
