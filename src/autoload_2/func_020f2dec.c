/* func_020f2dec @ 0x020f2dec, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020f4514(void *);
extern void func_020edb3c(void *);
extern char data_0213ed10;

void *func_020f2dec(void *self)
{
    *(void **) self = &data_0213ed10;
    func_020f4514(self);
    func_020edb3c(self);
    return self;
}
