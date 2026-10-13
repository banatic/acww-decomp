/* func_020ea450 @ 0x020ea450, 0x3c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_0213e660;

struct UnkStruct_020ea450 {
    unsigned int *unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
    unsigned int unk_0C;
    volatile unsigned int unk_10;
};

void func_020ea450(struct UnkStruct_020ea450 *self, unsigned int a, unsigned int b, unsigned int c)
{
    self->unk_00 = &data_0213e660;
    self->unk_04 = a;
    self->unk_08 = b;
    self->unk_0C = c;
    self->unk_10 = 0;
    self->unk_10 = 0x4000;
}
