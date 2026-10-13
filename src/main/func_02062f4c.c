/* func_02062f4c @ 0x02062f4c, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8c38(void *);
extern unsigned char data_020de62c;

void *func_02062f4c(void *self)
{
    *(void **) self = (void *) &data_020de62c;
    func_020a8c38(self);
    return self;
}
