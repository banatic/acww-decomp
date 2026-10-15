/* func_02081ff0 @ 0x02081ff0, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020a88ec(void *self);
extern char data_020e18ec;

void *func_02081ff0(void *self)
{
    func_020a88ec(self);
    *(void **) self = &data_020e18ec;
    return self;
}
