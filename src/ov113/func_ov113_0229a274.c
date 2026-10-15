/* func_ov113_0229a274 @ 0x0229a274, 0x50 bytes, Thumb, module ov113
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208054(void *self, int flag);
extern void func_ov113_0229a0ec(void *self);
extern int func_ov113_02299cd0(void *self);
extern int func_ov113_02299aa4(void *self);
extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;

void func_ov113_0229a274(void *self)
{
    unsigned int cond;

    if (func_ov002_02208054(self, 1)) {
        func_ov113_0229a0ec(self);
        return;
    }

    cond = (data_021fbdd8 && data_021fbddc) ? 1 : 0;
    if (cond > 0) {
        if (func_ov113_02299cd0(self)) {
            func_ov113_02299aa4(self);
        }
    }
}
