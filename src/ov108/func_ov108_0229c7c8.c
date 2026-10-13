/* func_ov108_0229c7c8 @ 0x0229c7c8, 0x48 bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229c7c8 {
    char pad_00[0x2b0];
    unsigned char unk_2B0;
};

extern int func_ov108_0229cc20(struct UnkStruct_0229c7c8 *self, unsigned char value);
extern int func_ov108_0229c2dc(struct UnkStruct_0229c7c8 *self, int value);

int func_ov108_0229c7c8(struct UnkStruct_0229c7c8 *self)
{
    int result;
    result = func_ov108_0229cc20(self, self->unk_2B0);
    if (func_ov108_0229c2dc(self, 0x20)) {
        result += 0x100;
    } else if (func_ov108_0229c2dc(self, 0x10)) {
        result -= 0x100;
    }
    return result + 8;
}
