/* func_02082184 @ 0x02082184, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8c38(void *p);
extern void func_020edb3c(void *p);
extern char data_020e1904;

void *func_02082184(void *self)
{
    *(void **) self = &data_020e1904;
    func_020a8c38(self);
    func_020edb3c(self);
    return self;
}
