/* func_020f3514 @ 0x020f3514, 0x24 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020f4514(void *self);
extern unsigned int data_0213eb70;

void *func_020f3514(void *self)
{
    *(unsigned int *) self = (unsigned int) &data_0213eb70;
    func_020f4514(self);
    return self;
}
