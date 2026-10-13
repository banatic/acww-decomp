/* func_ov145_02299fc8 @ 0x02299fc8, 0x24 bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02299fc8 {
    unsigned char pad_00[0xbc];
    unsigned short unk_BC;
};

extern int func_ov145_0229a06c(void *, void *, int, int);

void func_ov145_02299fc8(struct UnkStruct_02299fc8 *self)
{
    self->unk_BC = (unsigned short) func_ov145_0229a06c(self, (char *) self + 0x0c1c, 0x12b0, 0x38);
}
