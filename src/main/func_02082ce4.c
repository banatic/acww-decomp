/* func_02082ce4 @ 0x02082ce4, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020830d0(void *self);
extern void func_020edb3c(void *self);

extern unsigned char data_020e1a40[];

void *func_02082ce4(void *self)
{
    *(void **) self = (void *) data_020e1a40;
    func_020830d0(self);
    func_020edb3c(self);
    return self;
}
