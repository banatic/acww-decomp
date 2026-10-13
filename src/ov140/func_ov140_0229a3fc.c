/* func_ov140_0229a3fc @ 0x0229a3fc, 0x1e bytes, Thumb, module ov140
 * mwccarm 1.2/base -O4,s
 */

struct func_ov140_0229a3fc_unk {
    char pad_00[0x9c];
    int a;
    int b;
};

void func_ov140_0229a3fc(struct func_ov140_0229a3fc_unk *self, int v)
{
    self->a = v;
    if (v == -1) {
        self->b = 9;
    } else {
        self->b = 8;
    }
}
