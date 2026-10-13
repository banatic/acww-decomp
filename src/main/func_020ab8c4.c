/* func_020ab8c4 @ 0x020ab8c4, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020e3f9c;
extern void func_020a8c38(void *);

void *func_020ab8c4(void *self)
{
    *(void **) self = &data_020e3f9c;
    func_020a8c38(self);
    return self;
}
