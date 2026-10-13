/* func_ov068_02275228 @ 0x02275228, 0x20 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov068_022780b0;
extern void func_0202de4c(void *param1, void *param2);
extern void func_020edb3c(void *param);

void *func_ov068_02275228(void *self)
{
    *(void **) self = (void *) &data_ov068_022780b0;
    func_0202de4c(self, (void *) &data_ov068_022780b0);
    func_020edb3c(self);
    return self;
}
