/* func_ov114_0229d2d8 @ 0x0229d2d8, 0x2c bytes, Thumb, module ov114
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e930(const void *ptr);
extern void func_ov114_0229d244(void *self);

struct UnkStruct_0229d2d8 {
    unsigned char pad_00[0x121c];
    unsigned char sub[0x9f];
    unsigned char flag;
};

int func_ov114_0229d2d8(struct UnkStruct_0229d2d8 *self)
{
    if (self->flag == 2) {
        return func_0208e930(self->sub);
    } else {
        func_ov114_0229d244(self);
        return 1;
    }
}
