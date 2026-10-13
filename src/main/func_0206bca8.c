/* func_0206bca8 @ 0x0206bca8, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0206bca8 {
    char pad_00[0x4];
    void *unk_04;
    char pad_08[0x1c];
    unsigned char *unk_24;
    void *unk_28;
    int unk_2C;
    int unk_30;
    char pad_34[0x18];
    char unk_4C;
    char unk_4D;
    char unk_4E;
    char unk_4F;
    int unk_50;
    int unk_54;
    int unk_58;
    char pad_5C[0x7d];
    char unk_D9;
    char pad_DA[0x2];
    int unk_DC;
    int unk_E0;
} UnkStruct_0206bca8;

extern void func_0206c340(void *ptr);
extern void func_0206c1cc(void *ptr, void *ptr2);
extern void func_020680d0(void *ptr);

void func_0206bca8(UnkStruct_0206bca8 *p)
{
    p->unk_30 = 1;
    p->unk_2C = 0;
    p->unk_4C = 0;
    p->unk_4D = 0;
    p->unk_4E = 0;
    p->unk_4F = 0;
    p->unk_50 = 0;
    p->unk_54 = 0;
    p->unk_58 = 0;
    func_0206c340(p->unk_28);
    func_0206c1cc(p->unk_28, p->unk_04);
    func_020680d0(p->unk_24);
    p->unk_D9 = 0;
    p->unk_DC = 0;
    p->unk_E0 = 0;
    *(p->unk_24 + 0x1a49) = 0;
    *(p->unk_24 + 0x1a4a) = 0;
}
