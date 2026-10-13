/* func_ov106_0229ce64 @ 0x0229ce64, 0x44 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229ce64 {
    char pad_00[0xac];
    int unk_AC;
    int unk_B0;
    unsigned char unk_B4;
    char pad_B5[0xb58 - 0xb5];
    char unk_B58;
    char pad_B59[0x4180 - 0xb59];
    char unk_4180;
} UnkStruct_0229ce64;

extern int func_ov106_0229c364(UnkStruct_0229ce64 *obj, int arg);
extern void func_ov094_0229b5e8(void *p, int v1, int v2, void *p2);

void func_ov106_0229ce64(UnkStruct_0229ce64 *obj)
{
    if (func_ov106_0229c364(obj, 0x40) != 0) {
        return;
    }
    if (obj->unk_B4 == 0) {
        return;
    }
    if (obj->unk_B4 != 1) {
        return;
    }
    func_ov094_0229b5e8(&obj->unk_B58, obj->unk_AC, obj->unk_B0, &obj->unk_4180);
}
