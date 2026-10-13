/* func_ov003_0220c1e4 @ 0x0220c1e4, 0x3c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_0220c160(void *self);
extern void func_0203efb0(void *self, unsigned short value);
extern void func_ov003_0220c064(void *self, int value);
extern void *data_ov003_0223c5f4[];
extern unsigned char data_ov003_0223c5a0;

struct FuncOv003_0220c1e4Self {
    char pad_00[8];
    int unk_08;
};

int func_ov003_0220c1e4(struct FuncOv003_0220c1e4Self *self)
{
    func_ov003_0220c160(self);
    func_0203efb0(self, (unsigned short) self->unk_08);
    func_ov003_0220c064(self, 0);
    data_ov003_0223c5f4[self->unk_08] = self;
    data_ov003_0223c5a0++;
    return 1;
}
