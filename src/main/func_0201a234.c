/* func_0201a234 @ 0x0201a234, 0x46 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x48];
    char unk_48;
    char pad_49[0x4c - 0x49];
    unsigned int unk_4C;
    unsigned int unk_50;
    char pad_54[0x78 - 0x54];
    unsigned int unk_78;
    char pad_7C[0x80 - 0x7c];
    void *unk_80;
} UnkStruct_0201a234;

extern int func_0201a2e8(UnkStruct_0201a234 *p, unsigned int x);
extern int func_0201a2a8(UnkStruct_0201a234 *p, void *q, unsigned int a, unsigned int b);
extern int func_02056f94(void *p);

int func_0201a234(UnkStruct_0201a234 *param)
{
    int ret = 0;
    if (func_0201a2e8(param, param->unk_78)) {
        ret = func_0201a2a8(param, param->unk_80, (param->unk_50 << 4) >> 16, (param->unk_4C << 4) >> 16);
    } else {
        if (func_02056f94(&param->unk_48)) {
            ret = 1;
        }
    }
    return ret;
}
