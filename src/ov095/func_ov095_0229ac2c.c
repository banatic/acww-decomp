/* func_ov095_0229ac2c @ 0x0229ac2c, 0x5e bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov095_0229adc4(void *);
extern int func_ov095_0229ad18(void *);
extern int func_ov095_0229acc0(void *);
extern int func_ov095_0229ac8c(void *);

struct func_ov095_0229ac2c_s {
    unsigned char pad_00[0x42];
    unsigned char kind;
};

int func_ov095_0229ac2c(struct func_ov095_0229ac2c_s *self)
{
    int result = 0;

    if (func_ov095_0229adc4(self) != 0) {
        return 1;
    }

    switch (self->kind) {
        case 0:
            result = func_ov095_0229ad18(self);
            break;
        case 1:
        case 2:
            result = func_ov095_0229acc0(self);
            break;
        case 3:
        case 4:
        case 5:
            result = func_ov095_0229ac8c(self);
            break;
        default:
            break;
    }

    return result;
}
