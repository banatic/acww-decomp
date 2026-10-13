/* func_0205bbc4 @ 0x0205bbc4, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0205bbe8(void *self);
extern unsigned char data_020dd3b8;

void *func_0205bbc4(void *self)
{
    func_0205bbe8(self);
    *(void **) self = (void *) &data_020dd3b8;
    return self;
}
