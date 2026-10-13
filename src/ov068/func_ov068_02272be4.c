/* func_ov068_02272be4 @ 0x02272be4, 0x4c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov068_02272c30(unsigned int *self);
extern void func_02091278(void *r0, void *r1, int r2, int r3);
extern void func_ov068_02272bd4(void *r0);

void func_ov068_02272be4(unsigned int *self)
{
    unsigned int state = (self[0x78] << 4) >> 16;

    if (state < 0x25 || state > 0x32) {
        return;
    }
    if (state == 0x25) {
        func_ov068_02272c30(self);
    }
    func_02091278(*(void **) (self + 0xb9), (char *) self + 0x2cc, 0, 0);
    if (state == 0x32) {
        func_ov068_02272bd4(self);
    }
}
