/* func_020f95f8 @ 0x020f95f8, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int data_0213f250;
extern unsigned int *func_020f9868(void *self);
extern unsigned int *func_020f9848(void *self);

void *func_020f95f8(void *self)
{
    *(void **) self = (void *) &data_0213f250;
    func_020f9868(self);
    func_020f9848(self);
    return self;
}
