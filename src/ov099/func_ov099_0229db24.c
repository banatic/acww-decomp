/* func_ov099_0229db24 @ 0x0229db24, 0x70 bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov099_0229d894(void *);
extern void func_ov094_0229ad20(void *);
extern void func_ov094_0229b2b0(void *);
extern void func_ov002_02207f20(void *, int, int, int, int);
extern void func_02002708(int);
extern void func_ov002_02207e80(void *, int, int, int);
extern void func_ov002_02208090(void *, int);
extern void func_ov099_0229c29c(void *, int);
extern unsigned int func_ov002_02207f60(void *);

struct UnkStruct_0229db24 {
    char pad_00[0xcc];
    char sub1;
    char pad_CD[0xb2c - 0xcc - 1];
    char sub2;
    char pad_B2D[0x27ec - 0xb2c - 1];
    unsigned int unk_27EC;
};

void func_ov099_0229db24(struct UnkStruct_0229db24 *self)
{
    func_ov099_0229d894(self);
    func_ov094_0229ad20(&self->sub1);
    func_ov094_0229b2b0(&self->sub2);
    func_ov002_02207f20(self, 8, 0, 0, 0x30);
    func_02002708(6);
    func_ov002_02207e80(self, 6, 0, 0);
    func_ov002_02208090(self, 2);
    func_ov099_0229c29c(self, 1);
    func_ov099_0229c29c(self, 2);
    self->unk_27EC = func_ov002_02207f60(self);
}
