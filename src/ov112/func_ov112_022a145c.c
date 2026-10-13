/* func_ov112_022a145c @ 0x022a145c, 0x7c bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xa4];
    int unk_A4;
    int unk_A8;
} UnkStruct_022a145c;

int func_ov112_0229fb70(void *self);
void func_ov112_0229fe50(void *self, int x);
void func_ov112_0229f058(void *self);
int func_020ee45c(void *self);
void func_ov092_02299324(int arg, int a, int b);
void func_ov002_02207f04(void *self, int a, int b, int c, int d);
void func_ov002_02207e80(void *self, int a, int b, int c);
void func_ov002_02208090(void *self, int a);
int func_ov002_02207f60(void *self);

void func_ov112_022a145c(UnkStruct_022a145c *self)
{
    if (func_ov112_0229fb70(self)) {
        return;
    }
    func_ov112_0229fe50(self, 0x40);
    func_ov112_0229f058(self);
    func_ov092_02299324(func_020ee45c(self), 0x44, 1);
    func_ov002_02207f04(self, 0xa, 0, 0, 0x30);
    func_ov002_02207e80(self, 4, 0, -8);
    func_ov002_02207e80(self, 6, 0, -8);
    func_ov002_02208090(self, 0xd);
    self->unk_A4 = func_ov002_02207f60(self);
    self->unk_A8 = self->unk_A4;
}
