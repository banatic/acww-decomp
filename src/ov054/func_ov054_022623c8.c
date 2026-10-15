/* func_ov054_022623c8 @ 0x022623c8, 0x68 bytes, Thumb, module ov054
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_022623c8 {
    char pad_00[0x564];
    char data[0x2AC];
    unsigned short unk_810;
    unsigned short unk_812;
    unsigned char unk_814;
};

extern int func_02019c6c(char *p, int n, unsigned short v);
extern int func_0202ea40(void *self, void *local, int flag);
extern int func_020644cc(int v);
extern unsigned short data_020c80f8;

int func_ov054_022623c8(struct UnkStruct_022623c8 *self)
{
    unsigned char local[8];
    func_02019c6c(self->data, 1, self->unk_812);
    self->unk_810 = 0xFF;
    if (self->unk_814 == 0) {
        if (func_0202ea40((void *) self, local, 0) != 0) {
            self->unk_810 = (unsigned short) (func_020644cc(5) * 20 + 100);
        }
    }
    self->unk_812 = data_020c80f8;
    return 1;
}
