/* func_02050c90 @ 0x02050c90, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020edb3c(void *self);
extern char data_020dcf28;

void *func_02050c90(void *self)
{
    *(void **) self = (void *) &data_020dcf28;
    func_020edb3c(self);
    return self;
}
