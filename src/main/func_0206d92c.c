/* func_0206d92c @ 0x0206d92c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a887c(void *self);
extern void __arm func_020edb3c(void *self);

extern unsigned char data_020df1e8[];

void *func_0206d92c(void *self)
{
    *((void **) self) = (void *) data_020df1e8;
    func_020a887c(self);
    func_020edb3c(self);
    return self;
}
