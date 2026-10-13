/* func_ov090_0229919c @ 0x0229919c, 0x2e bytes, Thumb, module ov090
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_022080a0(void *p, int arg);

typedef struct {
    unsigned char pad_00[0x91];
    unsigned char unk_91;
    unsigned char unk_92;
} Obj_090;

void func_ov090_0229919c(Obj_090 *self)
{
    if (self->unk_92 <= 4) {
        self->unk_91 = 0;
        func_ov002_022080a0(self, 0);
    } else {
        self->unk_92 -= 4;
    }
}
