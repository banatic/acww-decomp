/* func_ov002_02209f14 @ 0x02209f14, 0x26 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208a198(void *p, int i);
extern int func_0208aeec(void *p);

struct UnkStruct_02209f14 {
    char pad_00[0x24];
    int unk_24;
};

int func_ov002_02209f14(struct UnkStruct_02209f14 *self)
{
    int a = func_0208a198((char *) self + 0xc, -1);
    int b = func_0208aeec(self);

    return a + (self->unk_24 + b);
}
