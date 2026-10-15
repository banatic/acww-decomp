/* func_020f2954 @ 0x020f2954, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020f4514(void *obj);
extern void func_020edb3c(void *obj);
extern char data_0213ee48;

void *func_020f2954(void *self)
{
    *(char **) self = &data_0213ee48;
    func_020f4514(self);
    func_020edb3c(self);
    return self;
}
