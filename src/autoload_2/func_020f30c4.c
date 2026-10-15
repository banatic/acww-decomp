/* func_020f30c4 @ 0x020f30c4, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020f4514(void *self);
extern void func_020edb3c(int argument0);
extern char data_0213ec74;

void *func_020f30c4(void *self)
{
    *(void **) self = &data_0213ec74;
    func_020f4514(self);
    func_020edb3c((int) self);
    return self;
}
