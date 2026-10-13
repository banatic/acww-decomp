/* func_ov144_0229a868 @ 0x0229a868, 0x2c bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov144_0229a17c(void *p);
extern void func_ov002_022080a0(void *p, int n);

struct S_f858 {
    unsigned char pad_00[0xc0];
    volatile unsigned char unk_C0;
};

void func_ov144_0229a868(struct S_f858 *s)
{
    if (s->unk_C0 != 0) {
        s->unk_C0 = s->unk_C0 - 1;
    } else {
        func_ov144_0229a17c(s);
        func_ov002_022080a0(s, 1);
    }
}
