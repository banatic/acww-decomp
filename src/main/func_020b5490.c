/* func_020b5490 @ 0x020b5490, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a9a40(void *self);
extern void func_020edb3c(void *self);
extern char data_020e51e8;

void *func_020b5490(void *self)
{
    ((void **) self)[0] = (void *) &data_020e51e8;
    func_020a9a40(self);
    func_020edb3c(self);
    return self;
}
