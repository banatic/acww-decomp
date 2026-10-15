/* func_ov096_022a16e4 @ 0x022a16e4, 0x60 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_022a16e4 {
    char pad_00[0x98];
    int unk_98;
};

extern int func_ov002_02207f3c(void *self, int flag);
extern int func_ov096_0229c2fc(void *self, int flag);
extern void func_020027f0(int n);
extern void func_ov096_0229c2dc(void *self, int n);
extern void func_ov002_02208090(void *self, int n);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern void func_ov002_02207e80(void *self, int a, int b, int c);
extern int func_ov002_02207f60(void *self);

void func_ov096_022a16e4(struct UnkStruct_022a16e4 *self)
{
    if (func_ov002_02207f3c(self, 0) != 0) {
        func_020027f0(6);
        func_ov096_0229c2dc(self, 2);
        if (func_ov096_0229c2fc(self, 0x80) != 0) {
            func_ov002_02208090(self, 7);
        } else {
            func_ov002_022080a0((void *) (self), 5);
            func_ov096_0229c2dc(self, 1);
        }
    } else {
        func_ov002_02207e80(self, 6, 0, 0);
    }
    self->unk_98 = func_ov002_02207f60(self);
}
