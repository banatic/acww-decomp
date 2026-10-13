/* func_ov045_02260d34 @ 0x02260d34, 0x18 bytes, Thumb, module ov045
 * mwccarm 1.2/base -O4,s
 */

extern void func_0201615c(void *);
extern char data_ov045_02261460;

void *func_ov045_02260d34(void *self)
{
    *(void **) self = (void *) &data_ov045_02261460;
    func_0201615c(self);
    return self;
}
