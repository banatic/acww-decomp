/* func_ov003_02230120 @ 0x02230120, 0x48 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *data_ov003_0223c0fc[];
extern void *data_020da13c[];
extern void *func_020ee660(void *a);
extern void func_ov003_02235d5c(void *a);
extern void func_0209d2b8(void *a);
extern unsigned char data_ov003_02260540;

void *func_ov003_02230120(char *self)
{
    func_020ee660(self);
    *(void **) self = data_020da13c;
    func_ov003_02235d5c(self);
    *(void **) self = data_ov003_0223c0fc;
    func_0209d2b8(self + 0x50);
    func_0209d2b8(self + 0x68);
    func_0209d2b8(self + 0x80);
    data_ov003_02260540 = 0;
    return self;
}
