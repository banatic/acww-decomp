/* func_ov095_0229aa3c @ 0x0229aa3c, 0x38 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229aa3c {
    unsigned char pad_00[0x28];
    unsigned int x;
    unsigned char pad_2C[0x16];
    unsigned char b;
};

void func_ov095_0229aa3c(struct UnkStruct_0229aa3c *self)
{
    switch (self->b) {
        case 0:
        case 3:
            break;
        case 1:
        case 2:
            self->x = 0x104;
            break;
        case 4:
        case 5:
            self->x = 0x107;
            break;
        default:
            break;
    }
}
