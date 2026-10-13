/* func_ov054_02260e58 @ 0x02260e58, 0xa0 bytes, Thumb, module ov054
 * mwccarm 1.2/base -O4,s
 */

extern void func_020157c8(void *p, int a, int b);
extern void func_02015828(void *p, int a);
extern int func_02098880(void *p);
extern int func_020a12d4(int a);
extern void func_0206844c(void *a, unsigned char *b, void *c);
struct B0Struct {
    unsigned char pad_00[0x808];
    unsigned int unk_808;
};
struct MData {
    unsigned char pad_00[0x1e];
    unsigned char unk_1E;
    unsigned char pad_1F[0x21];
    void *unk_40;
    unsigned char pad_44[0x6c];
    void *unk_B0;
};
extern int data_021dc7bc;
extern unsigned int data_ov054_02262fb4[];
inline unsigned char inline_fn(struct MData *arg0)
{
    return arg0->unk_1E;
}

void func_ov054_02260e58(struct MData *self)
{
    void *r6 = self->unk_40;
    unsigned int k = ((struct B0Struct *) self->unk_B0)->unk_808;
    void *r7 = *((void **) (((char *) data_ov054_02262fb4) + (12 * k)));
    int r4;
    int val;
    r4 = 0;
    switch (inline_fn(self)) {
        case 2:

        case 0x20:

        case 0x23:

        case 0x24:

        case 0x25:

        case 0x26:;
            func_020157c8(self, 0x2f, 0);
            func_02015828(self, 2);
            break;
            r4 = 2;

        case 19:
            r4 = func_02098880(&data_021dc7bc);
            if (func_020a12d4(r4) != 0) {
                r4 = 2;
            } else {
                r4 = (unsigned char) (r4 + 0x22);
            }
            break;

        default:
            break;
    }

    val = 0;
    if (r4 != val) {
        unsigned char c = (unsigned char) r4;
        func_0206844c(r6, &c, r7);
    }
}
