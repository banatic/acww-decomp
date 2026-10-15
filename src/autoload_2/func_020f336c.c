/* func_020f336c @ 0x020f336c, 0x24 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020f4514(void *self);

extern unsigned char data_0213ebd8[];

void *func_020f336c(void *self)
{
    *(unsigned int *) self = (unsigned int) data_0213ebd8;
    func_020f4514(self);
    return self;
}
