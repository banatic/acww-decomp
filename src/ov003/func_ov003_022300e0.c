/* func_ov003_022300e0 @ 0x022300e0, 0x40 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *data_ov003_0223c0fc[];
extern void *data_020da13c[];
extern void func_0209d2b4(void *a);
extern void func_ov003_02235d58(void *a);
extern void func_020ee62c(void *a);

void *func_ov003_022300e0(char *self)
{
    *(void **) self = data_ov003_0223c0fc;
    func_0209d2b4(self + 0x80);
    func_0209d2b4(self + 0x68);
    func_0209d2b4(self + 0x50);
    func_ov003_02235d58(self);
    *(void **) self = data_020da13c;
    func_020ee62c(self);
    return self;
}
