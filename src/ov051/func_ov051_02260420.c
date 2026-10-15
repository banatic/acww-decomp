/* func_ov051_02260420 @ 0x02260420, 0x28 bytes, Thumb, module ov051
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov051_0226193c;
extern void *func_ov051_02261058(void *p);
extern void *func_0202ee5c(void *p);

void *func_ov051_02260420(void *self)
{
    *(unsigned int *) self = (unsigned int) &data_ov051_0226193c;
    func_ov051_02261058((char *) self + 0x658);
    func_0202ee5c(self);
    return self;
}
