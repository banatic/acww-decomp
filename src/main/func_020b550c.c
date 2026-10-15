/* func_020b550c @ 0x020b550c, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020a8c38(void *self);
extern unsigned char data_020e51b8[];

void *func_020b550c(void *self)
{
    *(void **) self = data_020e51b8;
    func_020a8c38(self);
    return self;
}
