/* func_020392ec @ 0x020392ec, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020edb3c(void *self);

extern unsigned char data_020da5c8[];

void *func_020392ec(void *self)
{
    *(void **) self = (void *) data_020da5c8;
    func_020edb3c(self);
    return self;
}
