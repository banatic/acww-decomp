/* func_ov101_0229c5b8 @ 0x0229c5b8, 0x22 bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xb7];
    unsigned char type;
} UnkStruct_0229c5b8;

extern void func_ov101_0229c4e0(UnkStruct_0229c5b8 *self);
extern void func_ov101_0229cf80(UnkStruct_0229c5b8 *self);

void func_ov101_0229c5b8(UnkStruct_0229c5b8 *self)
{
    switch (self->type) {
        case 0:
            func_ov101_0229c4e0(self);
            break;
        case 1:
        default:
            func_ov101_0229cf80(self);
            break;
    }
}
