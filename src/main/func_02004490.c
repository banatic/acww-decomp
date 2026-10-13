/* func_02004490 @ 0x02004490, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_02004490(void *self)
{
    void *vtable;
    void (*func)(void *);

    vtable = *(void **) self;
    func = *(void (**)(void *))((char *) vtable + 8);
    func(self);
}
