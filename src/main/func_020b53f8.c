/* func_020b53f8 @ 0x020b53f8, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a941c(void *self);

extern unsigned char data_020e3e68[];
extern unsigned char data_020e5278[];

void *func_020b53f8(void *self)
{
    *(unsigned int *) self = (unsigned int) data_020e5278;
    *(unsigned int *) self = (unsigned int) data_020e3e68;
    func_020a941c(self);
    return self;
}
