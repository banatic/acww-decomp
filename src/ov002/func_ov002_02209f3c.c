/* func_ov002_02209f3c @ 0x02209f3c, 0x26 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208a1b0(void *p, int i);
extern int func_0208aef0(void *p);

struct UnkStruct_02209f3c {
    char pad_00[0x20];
    int unk_20;
};

int func_ov002_02209f3c(struct UnkStruct_02209f3c *self)
{
    int a = func_0208a1b0((char *) self + 0xc, -1);
    int b = func_0208aef0(self);

    return a + (self->unk_20 + b);
}
