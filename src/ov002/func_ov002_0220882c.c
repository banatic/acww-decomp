/* func_ov002_0220882c @ 0x0220882c, 0x18 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int _u32_div_f(unsigned int numerator, unsigned int denominator);

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
} UnkStruct_0220882c;

void func_ov002_0220882c(UnkStruct_0220882c *self, unsigned int denominator)
{
    self->unk_08 = 0x1000;
    self->unk_04 = _u32_div_f(0x1000, denominator);
}
