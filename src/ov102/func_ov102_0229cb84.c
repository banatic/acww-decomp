/* func_ov102_0229cb84 @ 0x0229cb84, 0x48 bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229cb84 {
    char pad_00[0x25a5];
    unsigned char byte;
};
extern int func_ov102_0229d1e8(struct UnkStruct_0229cb84 *, unsigned char);
extern int func_ov102_0229c2a8(struct UnkStruct_0229cb84 *, int);

int func_ov102_0229cb84(struct UnkStruct_0229cb84 *self)
{
    int result = func_ov102_0229d1e8(self, self->byte);
    if (func_ov102_0229c2a8(self, 0x20)) {
        result += 0x100;
    } else if (func_ov102_0229c2a8(self, 0x10)) {
        result -= 0x100;
    }
    result += 8;
    return result;
}
