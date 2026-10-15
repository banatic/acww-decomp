/* func_02078040 @ 0x02078040, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020a887c(void *self);
extern char data_020e1870;

void *func_02078040(void *self)
{
    *(void **) self = &data_020e1870;
    func_020a887c(self);
    return self;
}
