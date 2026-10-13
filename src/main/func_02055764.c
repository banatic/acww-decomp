/* func_02055764 @ 0x02055764, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02055ff4(void *self);

extern unsigned char data_020dd03c[];

void *func_02055764(void *self)
{
    *(void **) self = (void *) data_020dd03c;
    func_02055ff4(self);
    return self;
}
