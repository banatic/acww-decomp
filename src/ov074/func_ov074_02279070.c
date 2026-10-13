/* func_ov074_02279070 @ 0x02279070, 0x44 bytes, Thumb, module ov074
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02279070 {
    char pad_00[0x40];
    void *unk_40;
    char pad_44[0xb0 - 0x44];
    char *unk_B0;
} UnkStruct_02279070;

extern int func_0206fc6c(void);
extern void func_ov074_02278a90(char *a, char *b);
extern void func_0206844c(void *a, char *b, const void *c);
extern const int data_ov074_02279d14;

void func_ov074_02279070(UnkStruct_02279070 *this)
{
    void *o = this->unk_40;
    char code;

    code = 0xf;
    if (func_0206fc6c() != 0) {
        code = 0x1c;
        func_ov074_02278a90(this->unk_B0 + 0x714, this->unk_B0 + 0xec);
    }
    func_0206844c(o, &code, (const void *) &data_ov074_02279d14);
}
