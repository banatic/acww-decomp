/* func_020c336c @ 0x020c336c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0202eb20(void *);
extern void func_020edb3c(void *);

extern unsigned char data_020e7e14[];

void *func_020c336c(void *self)
{
    *(void **) self = (void *) data_020e7e14;
    func_0202eb20(self);
    func_020edb3c(self);
    return self;
}
