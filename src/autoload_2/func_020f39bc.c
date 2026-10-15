/* func_020f39bc @ 0x020f39bc, 0x24 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int data_0213ea38;
extern void *func_020f4514(void *self);

void *func_020f39bc(void *self)
{
    *(int *) self = (int) &data_0213ea38;
    func_020f4514(self);
    return self;
}
