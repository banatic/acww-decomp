/* func_0205602c @ 0x0205602c, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02056390(void *obj);
extern char data_020dd13c;

void *func_0205602c(void *self)
{
    ((void **) self)[0] = (void *) &data_020dd13c;
    func_02056390(self);
    return self;
}
