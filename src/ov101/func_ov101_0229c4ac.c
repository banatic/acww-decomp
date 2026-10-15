/* func_ov101_0229c4ac @ 0x0229c4ac, 0x34 bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x8C];
    char unk_8C;
    char pad_8D[0x2127];
    char unk_21B4;
} UnkStruct_0229c4ac;

extern void func_0206fc4c(int);
extern unsigned char *func_ov002_022080a0(UnkStruct_0229c4ac *self, unsigned char value);
extern int func_ov002_02207d24(char *ptr, int);
extern void func_ov101_0229c844(UnkStruct_0229c4ac *self);

void func_ov101_0229c4ac(UnkStruct_0229c4ac *self)
{
    func_0206fc4c(0);
    self->unk_8C = 3;
    func_ov002_022080a0(self, 1);
    func_ov002_02207d24(&self->unk_21B4, 1);
    func_ov101_0229c844(self);
}
