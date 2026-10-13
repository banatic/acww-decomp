/* func_ov146_02299650 @ 0x02299650, 0xe bytes, Thumb, module ov146
 * mwccarm 1.2/base -O4,s
 */

struct FuncOvl146Struct {
    unsigned char pad_00[0xac];
    unsigned short unk_AC;
};

void func_ov146_02299650(struct FuncOvl146Struct *self, unsigned short bits)
{
    self->unk_AC &= ~bits;
}
