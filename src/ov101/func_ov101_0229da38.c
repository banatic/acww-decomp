/* func_ov101_0229da38 @ 0x0229da38, 0x60 bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229da38 {
    char pad_00[0x98];
    int unk_98;
};

extern int func_ov002_02207d24(void *addr, int n);
extern void func_ov101_0229c844(void *self);
extern int func_020ee45c(void *self);
extern void func_ov092_02299324(int v, int a, int b);
extern void func_ov002_02207f04(void *self, int a, int b, int c, int d);
extern void func_ov002_02207e80(void *self, int a, int b, int c);
extern void func_ov002_02208090(void *self, int n);
extern int func_ov002_02207f60(void *self);

void func_ov101_0229da38(struct UnkStruct_0229da38 *self)
{
    int r;

    func_ov002_02207d24((char *) self + 0x21b4, 1);
    func_ov101_0229c844(self);
    r = func_020ee45c(self);
    func_ov092_02299324(r, 0x44, 1);
    func_ov002_02207f04(self, 8, 0, 0, 0x30);
    func_ov002_02207e80(self, 6, 0, (int) 0xfffffff0);
    func_ov002_02208090(self, 4);
    self->unk_98 = func_ov002_02207f60(self);
}
