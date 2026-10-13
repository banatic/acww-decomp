/* func_020ab948 @ 0x020ab948, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a9a40(void *self);
extern char data_020e3fcc;

void *func_020ab948(void *self)
{
    *(unsigned int *) self = (unsigned int) &data_020e3fcc;
    func_020a9a40(self);
    return self;
}
