/* func_020f2c64 @ 0x020f2c64, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020f4514(void *);
extern void func_020edb3c(void *);
extern unsigned int data_0213ed78;

void *func_020f2c64(void *self)
{
    *(unsigned int *) self = (unsigned int) &data_0213ed78;
    func_020f4514(self);
    func_020edb3c(self);
    return self;
}
