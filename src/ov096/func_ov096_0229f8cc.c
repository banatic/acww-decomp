/* func_ov096_0229f8cc @ 0x0229f8cc, 0x3e bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov096_0229e9f8(void *a, int b, unsigned char c, int d);
extern int func_ov096_0229f290(void *a, void *b);
extern int func_ov096_0229f200(void *a, void *b);
extern void func_ov096_0229f90c(void *a, void *b, int c);

typedef struct {
    char pad_00[0xa4];
    int unk_A4;
    int unk_A8;
} StructSelf;

void func_ov096_0229f8cc(StructSelf *self, void *other, void *third, int d, unsigned char e)
{
    func_ov096_0229e9f8(self, d, e, d);
    self->unk_A4 = func_ov096_0229f290(self, other);
    self->unk_A8 = func_ov096_0229f200(self, other);
    func_ov096_0229f90c(self, third, 4);
}
