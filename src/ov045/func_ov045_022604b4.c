/* func_ov045_022604b4 @ 0x022604b4, 0x18 bytes, Thumb, module ov045
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020a88ec(void *p);
extern char data_ov045_0226142c;

void *func_ov045_022604b4(void *self)
{
    func_020a88ec(self);
    *(void **) self = &data_ov045_0226142c;
    return self;
}
