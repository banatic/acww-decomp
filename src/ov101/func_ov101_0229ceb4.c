/* func_ov101_0229ceb4 @ 0x0229ceb4, 0x44 bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229ceb4 {
    char pad_00[0xaf];
    unsigned char unk_AF;
    char pad_B0[0xb2 - 0xaf - 1];
    char unk_B2;
    char pad_B3[0xb6 - 0xb2 - 1];
    unsigned char unk_B6;
    char pad_B7[0x21b4 - 0xb6 - 1];
    char unk_21B4[1];
} UnkStruct_0229ceb4;

extern int func_ov002_02207d24(void *ptr, int num);
extern void func_ov101_0229c970(UnkStruct_0229ceb4 *obj, int value);
extern void func_ov101_0229ca00(UnkStruct_0229ceb4 *obj);

void func_ov101_0229ceb4(UnkStruct_0229ceb4 *obj, int value)
{
    obj->unk_B2 = value;
    func_ov002_02207d24(obj->unk_21B4, 1);
    func_ov101_0229c970(obj, value);
    if (obj->unk_AF == 1) {
        obj->unk_B6 = 7;
    }
    func_ov101_0229ca00(obj);
}
