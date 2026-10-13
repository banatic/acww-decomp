/* func_ov049_022629e4 @ 0x022629e4, 0x68 bytes, Thumb, module ov049
 * mwccarm 1.2/base -O4,s
 */

extern void func_02019c6c(void *, int, unsigned short);
extern int func_020644cc(int);
extern int func_0202ea40(void *, void *, int);
extern unsigned short data_020c80f8;

typedef struct {
    unsigned char pad_00[0x564];
    int unk_564;
    unsigned char pad_568[0x408]; // 0x970 - 0x568
    unsigned short unk_970;
    unsigned short unk_972;
    unsigned char pad_974;
    unsigned char unk_975;
} UnkStruct_022629e4;

int func_ov049_022629e4(UnkStruct_022629e4 *self)
{
    int local[2];

    func_02019c6c(&self->unk_564, 1, self->unk_972);
    self->unk_972 = data_020c80f8;
    self->unk_970 = (unsigned short) (func_020644cc(5) * 20 + 100);
    if (func_0202ea40(self, local, 2) != 0) {
        self->unk_975 = 1;
    } else {
        self->unk_975 = 0;
    }
    return 1;
}
