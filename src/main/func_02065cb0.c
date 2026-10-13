/* func_02065cb0 @ 0x02065cb0, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a88ec(void *);
extern char data_020de770;

void *func_02065cb0(void *self)
{
    func_020a88ec(self);
    *(void **) self = &data_020de770;
    return self;
}
