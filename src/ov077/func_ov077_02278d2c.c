/* func_ov077_02278d2c @ 0x02278d2c, 0x20 bytes, Thumb, module ov077
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0202eb20(void *self);
extern void func_020edb3c(void *self);
extern unsigned int data_ov077_022797fc;

void *func_ov077_02278d2c(void *self)
{
    *(unsigned int *) self = (unsigned int) &data_ov077_022797fc;
    func_0202eb20(self);
    func_020edb3c(self);
    return self;
}
