/* func_ov099_0229c63c @ 0x0229c63c, 0x4c bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208ae4(void *);
extern int func_ov002_02208ad8(void *, int);
extern void func_ov002_0220a0b4(void *, int, int);
extern void func_ov002_0220a374(void *, int);

struct UnkStruct_0229c63c {
    char pad_00[0x2274];
    char unk_2274;
    char pad_2275[0x63];
    char unk_22D8;
    char pad_22D9[0x633];
    unsigned char flag;
};

void func_ov099_0229c63c(struct UnkStruct_0229c63c *self)
{
    int a;
    int b;
    self->flag = 0;
    a = func_ov002_02208ae4(&self->unk_22D8);
    b = func_ov002_02208ad8(&self->unk_22D8, self->flag);
    func_ov002_0220a0b4(&self->unk_2274, a, b);
    func_ov002_0220a374(&self->unk_2274, 7);
}
