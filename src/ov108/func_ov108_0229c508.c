/* func_ov108_0229c508 @ 0x0229c508, 0x24 bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x2b4];
    unsigned char flag;
} UnkStruct_0229c508;

extern void func_ov108_0229cdb8(UnkStruct_0229c508 *self);
extern void func_ov108_0229cf4c(UnkStruct_0229c508 *self);

void func_ov108_0229c508(UnkStruct_0229c508 *self)
{
    switch (self->flag) {
        case 0:
            func_ov108_0229cdb8(self);
            break;
        case 1:
        default:
            func_ov108_0229cf4c(self);
            break;
    }
}
