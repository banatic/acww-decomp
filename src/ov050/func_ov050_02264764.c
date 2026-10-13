/* func_ov050_02264764 @ 0x02264764, 0x70 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02264764 {
    unsigned char pad_00[0x564];
    unsigned char unk_564[0x1c8];
    unsigned char unk_72C;
    unsigned char pad_72D;
    unsigned short unk_72E;
    unsigned short unk_730;
} UnkStruct_02264764;

extern void func_02019c6c(void *address, int n, unsigned short value);
extern int func_020644cc(int n);
extern int func_ov050_02260510(UnkStruct_02264764 *self);
extern int func_0202ea40(UnkStruct_02264764 *self, int *local, int n);
extern unsigned short data_020c80f8;

int func_ov050_02264764(UnkStruct_02264764 *self)
{
    int local[2];

    func_02019c6c(&self->unk_564, 1, self->unk_730);
    self->unk_72E = func_020644cc(5) * 20 + 100;
    self->unk_730 = data_020c80f8;
    if (func_ov050_02260510(self) != 0 && func_0202ea40(self, local, 3) != 0) {
        self->unk_72C = 1;
    } else {
        self->unk_72C = 0;
    }
    return 1;
}
