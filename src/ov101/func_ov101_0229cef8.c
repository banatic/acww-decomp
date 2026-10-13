/* func_ov101_0229cef8 @ 0x0229cef8, 0x88 bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x9C];
    int word1;
    int word2;
    char pad_A4[0xB0 - 0xA4];
    unsigned char byte1;
    unsigned char byte2;
    char pad_B2[0xB9 - 0xB2];
    unsigned char byte3;
    char pad_BA[0x21B4 - 0xBA];
    char unk_21B4;
} UnkStruct_0229cef8;
extern void func_ov002_02208098(UnkStruct_0229cef8 *p, int flag);
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;
extern int func_ov101_0229cd08(UnkStruct_0229cef8 *p, int b);
extern int func_ov101_0229ccd0(UnkStruct_0229cef8 *p, int b);
extern void func_ov002_02207cf8(void *p);
extern void func_ov002_02207d00(void *p);
extern int func_ov101_0229cc50(UnkStruct_0229cef8 *p, int val);
extern void func_ov094_022999cc(void);
void func_ov101_0229cef8(UnkStruct_0229cef8 *self, int val)
{
    unsigned char a;
    unsigned char b;
    self->byte1 = val;
    func_ov002_02208098(self, 1);
    a = data_021f6c58;
    b = data_021f6c54;
    self->word1 = func_ov101_0229cd08(self, self->byte1) - a;
    self->word2 = func_ov101_0229ccd0(self, self->byte1) - b;
    self->byte2 = val;
    func_ov002_02207cf8(&self->unk_21B4);
    func_ov002_02207d00(&self->unk_21B4);
    self->byte3 = 2;
    if (func_ov101_0229cc50(self, val) == 0) {
        func_ov094_022999cc();
    }
}
