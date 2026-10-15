/* func_ov106_0229ca5c @ 0x0229ca5c, 0x34 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov106_0229cc84(void *self);
extern int func_ov106_0229cc74(void *self);
extern void func_ov002_0220a0b4(void *p, int a, int b);
extern void func_ov002_0220a374(void *p, int a);

struct UnkStruct_0229ca5c {
    char pad_00[0x22a0];
    int unk_22A0;
};

void func_ov106_0229ca5c(struct UnkStruct_0229ca5c *self)
{
    int v1 = func_ov106_0229cc84(self);
    int v2 = func_ov106_0229cc74(self);
    func_ov002_0220a0b4(&self->unk_22A0, v1, v2);
    func_ov002_0220a374(&self->unk_22A0, 1);
}
