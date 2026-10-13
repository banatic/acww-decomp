/* func_ov105_0229d7f4 @ 0x0229d7f4, 0x38 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov105_0229d0f8(void *a, void *b, void *c);
extern int func_ov105_0229d530(void *a, void *b);
extern int func_ov105_0229d4c4(void *a, void *b);
extern void func_ov105_0229d870(void *a, void *b, int n);

typedef struct UnkStruct_0229d7f4 {
    char pad_00[0xac];
    int unk_AC;
    int unk_B0;
} UnkStruct_0229d7f4;

void func_ov105_0229d7f4(UnkStruct_0229d7f4 *a, void *b, void *c)
{
    func_ov105_0229d0f8(a, b, c);
    a->unk_AC = func_ov105_0229d530(a, b);
    a->unk_B0 = func_ov105_0229d4c4(a, b);
    func_ov105_0229d870(a, c, 4);
}
