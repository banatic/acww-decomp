/* func_ov100_0229c970 @ 0x0229c970, 0x24 bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x2925];
    unsigned char flag;
} UnkStruct_0229c970;

extern void func_ov100_0229ca1c(UnkStruct_0229c970 *self);
extern void func_ov100_0229d8b0(UnkStruct_0229c970 *self);

void func_ov100_0229c970(UnkStruct_0229c970 *self)
{
    switch (self->flag) {
        case 0:
            func_ov100_0229ca1c(self);
            break;
        case 1:
        default:
            func_ov100_0229d8b0(self);
            break;
    }
}
