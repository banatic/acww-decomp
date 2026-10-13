/* func_02033ca8 @ 0x02033ca8, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02034294(void *arg);
extern void func_0202fed4(void *arg);

extern unsigned char data_020da21c[];

void *func_02033ca8(void *self)
{
    *(void **) self = (void *) data_020da21c;
    func_02034294((char *) self + 0x38);
    func_0202fed4(self);
    return self;
}
