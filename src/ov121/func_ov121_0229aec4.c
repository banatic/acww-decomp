/* func_ov121_0229aec4 @ 0x0229aec4, 0x3c bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xb0];
    unsigned char b0;
} UnkStruct_0229aec4;

extern void func_ov121_0229af00(UnkStruct_0229aec4 *obj, int a, int b);

void func_ov121_0229aec4(UnkStruct_0229aec4 *obj, int value)
{
    unsigned char b = obj->b0;
    if (value == b) {
        return;
    }
    if (b != 0x18) {
        func_ov121_0229af00(obj, b, 2);
    }
    obj->b0 = value;
    if (obj->b0 != 0x18) {
        func_ov121_0229af00(obj, obj->b0, 6);
    }
}
