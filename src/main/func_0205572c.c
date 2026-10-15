/* func_0205572c @ 0x0205572c, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02055ff4(void *obj);

extern unsigned char data_020dd03c[];

void *func_0205572c(void *self)
{
    *(void **) self = (void *) data_020dd03c;
    func_02055ff4(self);
    return self;
}
