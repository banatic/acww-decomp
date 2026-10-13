/* func_ov147_0229a01c @ 0x0229a01c, 0x38 bytes, Thumb, module ov147
 * mwccarm 1.2/base -O4,s
 */

extern void func_02035638(int);
extern void func_02035624(int);
extern void func_02035684(int, int, int);

typedef struct {
    char pad_00[0xa3];
    unsigned char unk_A3;
} UnkStruct_0229a01c;

void func_ov147_0229a01c(UnkStruct_0229a01c *self)
{
    unsigned char val = self->unk_A3;
    if (val == 0) {
        return;
    }
    if (val == 1) {
        func_02035638(0);
    } else if (val == 2) {
        func_02035624(1);
    }
    func_02035684(1, 0xf, 0xf);
    self->unk_A3 = 0;
}
