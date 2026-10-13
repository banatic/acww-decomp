/* func_ov113_0229a6d4 @ 0x0229a6d4, 0x48 bytes, Thumb, module ov113
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f48(void *self, int a);
extern void func_ov002_022080a0(void *self, int a);
extern int func_0206fe60(void);
extern void func_ov002_02207e80(void *self, int a, int b, int c);
extern int func_ov002_02207f60(void *self);
extern void func_ov113_0229a108(void *self);
extern void func_ov113_0229a0ec(void *self);

typedef struct {
    char pad_00[0x94];
    int unk_94;
} self_t;

void func_ov113_0229a6d4(self_t *self)
{
    if (func_ov002_02207f48(self, 1)) {
        func_ov002_022080a0(self, 2);
        if (func_0206fe60()) {
            func_ov113_0229a108(self);
        } else {
            func_ov113_0229a0ec(self);
        }
    }
    func_ov002_02207e80(self, 2, 0, 0);
    self->unk_94 = func_ov002_02207f60(self);
}
