/* func_02036ba4 @ 0x02036ba4, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0203564c(int);

struct UnkStruct_02036ba4 {
    unsigned char pad_00[8];
    unsigned short unk_08;
};

void func_02036ba4(struct UnkStruct_02036ba4 *self, unsigned short value)
{
    func_0203564c(0x1f);
    self->unk_08 = value;
}
