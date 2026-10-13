/* func_ov120_0229b168 @ 0x0229b168, 0x1e bytes, Thumb, module ov120
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov120_0229a448(void *arg, int arg2);

struct func_ov120_0229b168_struct {
    unsigned char pad_00[0xa1];
    unsigned char unk_A1;
    unsigned char unk_A2;
};

unsigned char func_ov120_0229b168(struct func_ov120_0229b168_struct *self)
{
    if (func_ov120_0229a448(self, 1) != 0) {
        return self->unk_A2;
    } else {
        return self->unk_A1;
    }
}
