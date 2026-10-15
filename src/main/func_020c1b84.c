/* func_020c1b84 @ 0x020c1b84, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0202eb70(void *self);
extern char data_020e7bd0;

void *func_020c1b84(void *self)
{
    func_0202eb70(self);
    *(void **) self = &data_020e7bd0;
    return self;
}
