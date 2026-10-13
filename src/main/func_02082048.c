/* func_02082048 @ 0x02082048, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8cac(void *self);
extern char data_020e191c;

void *func_02082048(void *self)
{
    func_020a8cac(self);
    *(char **) self = &data_020e191c;
    return self;
}
