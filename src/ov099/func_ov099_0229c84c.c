/* func_ov099_0229c84c @ 0x0229c84c, 0x34 bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x2900];
    unsigned short unk_2900;
    unsigned char unk_2902;
    unsigned char unk_2903;
} UnkStruct_0229c84c;

extern void func_ov099_0229ce28(UnkStruct_0229c84c *obj, int param, unsigned short a, unsigned char b);

void func_ov099_0229c84c(UnkStruct_0229c84c *obj, int param)
{
    if (obj->unk_2903 != 1 && obj->unk_2903 == 2) {
        func_ov099_0229ce28(obj, param, obj->unk_2900, obj->unk_2902);
    }
    obj->unk_2903 = 0;
}
