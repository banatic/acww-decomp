/* func_ov046_02261378 @ 0x02261378, 0x50 bytes, Thumb, module ov046
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02261378 {
    char pad_00[0x40];
    void *unk_40;
    char pad_44[0xc4 - 0x44];
    char unk_C4;
    char unk_C5;
} UnkStruct_02261378;

extern int func_0206fc6c(void);
extern int func_020b1558(void);
extern void func_0206844c(void *a, char *b, const void *c);
extern const int data_ov046_02261fe8;

void func_ov046_02261378(UnkStruct_02261378 *this)
{
    void *o = this->unk_40;
    char code;

    code = 0x1d;
    if (func_0206fc6c() != 0) {
        code = 0x38;
    } else {
        this->unk_C5 = (char) (0x10 - func_020b1558());
        this->unk_C4 = 0;
        code = 0x1d;
    }
    func_0206844c(o, &code, (const void *) &data_ov046_02261fe8);
}
