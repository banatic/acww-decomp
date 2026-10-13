/* func_ov070_022796c0 @ 0x022796c0, 0x2c bytes, Thumb, module ov070
 * mwccarm 1.2/base -O4,s
 */

extern void func_0202eb20(void *);
extern void func_02138c48(void *, int, int, void (*)(void));
extern void func_020051b0(void);
extern char data_ov070_02279dbc[];

void *func_ov070_022796c0(void *self)
{
    *(void **) self = &data_ov070_02279dbc;
    func_02138c48((char *) self + 0xc4, 3, 2, func_020051b0);
    func_0202eb20(self);
    return self;
}
