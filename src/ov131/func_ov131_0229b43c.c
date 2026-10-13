/* func_ov131_0229b43c @ 0x0229b43c, 0x38 bytes, Thumb, module ov131
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xf8];
    unsigned char unk_F8;
    unsigned char pad_F9[0x2c4 - 0xf8 - 1];
    unsigned char unk_2C4;
} UnkStruct_0229b43c;

extern void func_ov130_0229a2b4(void *);
extern int func_ov130_02299ddc(void *);
extern void func_ov002_0220a658(void *, int);
extern void func_ov002_0220a63c(void *, int);

void func_ov131_0229b43c(UnkStruct_0229b43c *self)
{
    int result;
    func_ov130_0229a2b4(&self->unk_2C4);
    result = func_ov130_02299ddc(&self->unk_2C4);
    if (result == 0) {
        func_ov002_0220a658(&self->unk_F8, 6);
    } else {
        func_ov002_0220a63c(&self->unk_F8, 6);
    }
}
