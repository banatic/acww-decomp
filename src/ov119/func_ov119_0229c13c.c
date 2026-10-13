/* func_ov119_0229c13c @ 0x0229c13c, 0x64 bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208054(void *self, int a);
extern void func_ov119_0229bc14(void *self);
extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;
extern int func_ov119_0229b0f8(void *self, unsigned char a, unsigned char b);
extern void func_ov119_0229b188(void *self);

void func_ov119_0229c13c(void *self)
{
    unsigned int cond;
    if (func_ov002_02208054(self, 1)) {
        func_ov119_0229bc14(self);
        return;
    }
    if (data_021fbdd8 == 0) {
        goto zero;
    }
    if (data_021fbddc == 0) {
        goto zero;
    }
    cond = 1;
    goto done;
zero:
    cond = 0;
done:
    if (cond) {
        int r = func_ov119_0229b0f8(self, data_021f6c58, data_021f6c54);
        if (r != 0x17) {
            *((unsigned char *) self + 0xa0) = r;
            func_ov119_0229b188(self);
        }
    }
}
