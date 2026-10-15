/* func_ov107_0229cb3c @ 0x0229cb3c, 0x3c bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229cb3c {
    unsigned char pad_00[0x8C];
    unsigned char unk_8C;
    unsigned char pad_8D[0xB9 - 0x8D];
    unsigned char unk_B9;
};

extern void func_0206fc80(int);
extern void func_0206fc4c(int);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern int func_ov002_02207d24(void *, int);
extern void func_ov107_0229ce90(struct UnkStruct_0229cb3c *);

void func_ov107_0229cb3c(struct UnkStruct_0229cb3c *self)
{
    func_0206fc80(self->unk_B9);
    func_0206fc4c(1);
    self->unk_8C = 3;
    func_ov002_022080a0((void *) (self), 1);
    func_ov002_02207d24((char *) self + 0x21CC, 1);
    func_ov107_0229ce90(self);
}
