/* func_02062de0 @ 0x02062de0, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a887c(void *self);
extern void func_020edb3c(void *self);
extern char data_020de614;

void *func_02062de0(void *self)
{
    *(void **) self = &data_020de614;
    func_020a887c(self);
    func_020edb3c(self);
    return self;
}
