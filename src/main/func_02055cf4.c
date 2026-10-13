/* func_02055cf4 @ 0x02055cf4, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02055b40(void *arg);
extern char data_020dd12c;

void *func_02055cf4(void *arg)
{
    void *self = arg;
    *(void **) self = &data_020dd12c;
    func_02055b40(self);
    return self;
}
