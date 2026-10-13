/* func_ov049_022620e8 @ 0x022620e8, 0x18 bytes, Thumb, module ov049
 * mwccarm 1.2/base -O4,s
 */

extern void func_0202eb70(void *);

extern unsigned char data_ov049_022634b4[];

void *func_ov049_022620e8(void *self)
{
    func_0202eb70(self);
    *(void **) self = (void *) data_ov049_022634b4;
    return self;
}
