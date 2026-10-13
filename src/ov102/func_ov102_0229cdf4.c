/* func_ov102_0229cdf4 @ 0x0229cdf4, 0x64 bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229cdf4 {
    char pad_00[0x218c];
    char sub[0x415];
    unsigned char unk_25A1;
    char pad_25A2[3];
    unsigned char unk_25A5;
} UnkStruct_0229cdf4;

extern int func_ov102_0229d464(UnkStruct_0229cdf4 *obj, unsigned char byte);
extern int func_ov102_0229d454(UnkStruct_0229cdf4 *obj, unsigned char byte);
extern int func_ov102_0229d074(UnkStruct_0229cdf4 *obj, unsigned char byte);
extern void func_ov002_02207cf0(char *sub);
extern void func_ov002_02207cf8(char *sub);

void func_ov102_0229cdf4(UnkStruct_0229cdf4 *obj)
{
    if (func_ov102_0229d464(obj, obj->unk_25A5) != 0 || func_ov102_0229d454(obj, obj->unk_25A5) != 0) {
        if (func_ov102_0229d074(obj, obj->unk_25A5) != 0) {
            func_ov002_02207cf0(obj->sub);
        } else {
            obj->unk_25A1 = obj->unk_25A5;
            func_ov002_02207cf8(obj->sub);
        }
    } else {
        func_ov002_02207cf0(obj->sub);
    }
}
