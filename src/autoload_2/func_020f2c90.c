/* func_020f2c90 @ 0x020f2c90, 0x24 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020f4514(void *arg0);

extern unsigned char data_0213ed78[];

void *func_020f2c90(void *self)
{
    *(void **) self = (void *) data_0213ed78;
    func_020f4514(self);
    return self;
}
