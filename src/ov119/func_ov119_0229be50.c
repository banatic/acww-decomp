/* func_ov119_0229be50 @ 0x0229be50, 0x3c bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229be50 {
    unsigned char pad_00[0xA0];
    unsigned char b0;
    unsigned char pad_A1[0x10];
    unsigned char b1;
};

extern void func_ov119_0229b9a4(struct UnkStruct_0229be50 *self);
extern void func_ov119_0229b510(struct UnkStruct_0229be50 *self);
extern void func_ov119_0229b49c(struct UnkStruct_0229be50 *self);

void func_ov119_0229be50(struct UnkStruct_0229be50 *self)
{
    if (self->b1 != 0) {
        self->b1--;
    } else {
        func_ov119_0229b9a4(self);
        if (self->b0 == 0x16) {
            func_ov119_0229b510(self);
        } else {
            func_ov119_0229b49c(self);
        }
    }
}
