/* func_ov096_022a053c @ 0x022a053c, 0x94 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_022a053c UnkStruct_022a053c;

extern int func_ov002_02209f9c(const char *p);
extern void func_ov096_0229e79c(UnkStruct_022a053c *self);
extern int func_ov096_0229c2fc(UnkStruct_022a053c *self, int a);
extern void func_ov096_0229e9f8(UnkStruct_022a053c *self, unsigned short a, int b);
extern void func_ov096_0229f90c(UnkStruct_022a053c *self, unsigned char a, int b);
extern void func_ov096_0229c2dc(UnkStruct_022a053c *self, int a);
extern void func_ov096_0229eb14(UnkStruct_022a053c *self);
extern int func_ov002_02208098(UnkStruct_022a053c *self, int a);
extern void func_ov094_022999d8(int x);
extern void func_ov096_0229ea5c(UnkStruct_022a053c *self);

struct UnkStruct_022a053c {
    char pad_00[0x8d];
    unsigned char unk_8D;
    char pad_8E[0x20];
    unsigned short unk_AE;
    char pad_B0[5];
    unsigned char unk_B5;
    char pad_B6;
    unsigned char unk_B7;
    char pad_B8;
    unsigned char unk_B9;
    char pad_BA[0x2446];
    char unk_2500;
};

void func_ov096_022a053c(UnkStruct_022a053c *self)
{
    if (func_ov002_02209f9c(&self->unk_2500) == 0) {
        if (self->unk_B5 == self->unk_B7) {
            func_ov096_0229e79c(self);
            if (func_ov096_0229c2fc(self, 0x2000) != 0) {
                func_ov096_0229e9f8(self, self->unk_AE, 0);
                func_ov096_0229f90c(self, self->unk_B9, 4);
                func_ov096_0229c2dc(self, 0x2000);
            }
        } else {
            func_ov096_0229f90c(self, self->unk_B7, 4);
        }
        if (self->unk_8D == 0x14) {
            func_ov096_0229eb14(self);
            func_ov094_022999d8(func_ov002_02208098(self, 0xa));
        }
    } else {
        func_ov096_0229ea5c(self);
    }
}
