/* func_02089c58 @ 0x02089c58, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020e2008;
extern void func_0208a07c(void *);

void *func_02089c58(void *self)
{
    *(void **) self = &data_020e2008;
    func_0208a07c(self);
    return self;
}
