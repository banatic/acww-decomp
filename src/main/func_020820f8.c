/* func_020820f8 @ 0x020820f8, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020a8cac(void *self);

extern unsigned char data_020e18d4[];

void *func_020820f8(void *self)
{
    func_020a8cac(self);
    *(void **) self = (void *) data_020e18d4;
    return self;
}
