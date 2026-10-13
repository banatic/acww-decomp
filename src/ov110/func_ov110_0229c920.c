/* func_ov110_0229c920 @ 0x0229c920, 0x22 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xf9];
    unsigned char type;
} UnkStruct_0229c920;

extern void func_ov110_0229c9c8(UnkStruct_0229c920 *self);
extern void func_ov110_0229d840(UnkStruct_0229c920 *self);

void func_ov110_0229c920(UnkStruct_0229c920 *self)
{
    switch (self->type) {
        case 0:
            func_ov110_0229c9c8(self);
            break;
        case 1:
        default:
            func_ov110_0229d840(self);
            break;
    }
}
