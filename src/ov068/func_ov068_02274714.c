/* func_ov068_02274714 @ 0x02274714, 0x20 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void func_0202eb70(void *obj);
extern void func_020f9680(void *obj);
extern char data_ov068_02277dc0;

void *func_ov068_02274714(void *self)
{
    func_0202eb70(self);
    *(void **) self = (void *) &data_ov068_02277dc0;
    func_020f9680((char *) self + 0xbc);
    return self;
}
