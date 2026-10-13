/* func_02082d04 @ 0x02082d04, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020e1a40;
extern void func_020830d0(void *);

void *func_02082d04(void *self)
{
    *(void **) self = &data_020e1a40;
    func_020830d0(self);
    return self;
}
