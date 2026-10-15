/* func_02058c60 @ 0x02058c60, 0x2e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x54];
    unsigned int unk_54;
    char pad_58[8];
    char unk_60;
    char pad_61[0x75];
    unsigned short unk_D6;
} UnkStruct_02058c60;

extern void func_02059674(void *ptr, int);
extern int func_02091254(int, void *, int, int);

void func_02058c60(UnkStruct_02058c60 *param)
{
    int zero = 0;
    func_02059674(param, 1);
    param->unk_D6 = 0;
    if (param->unk_54 == 2) {
        param->unk_54 = 0;
    }
    func_02091254(0x93, &param->unk_60, zero, zero);
}
