/* func_ov120_0229a870 @ 0x0229a870, 0x78 bytes, Thumb, module ov120
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov120_0229a448(void *, int);
extern int func_ov120_0229a81c(void *);
extern int func_ov120_0229a7cc(void *);
extern void func_ov120_0229abdc(void *, int);
extern void func_ov120_0229a6d0(void *);
extern void func_ov002_0220a0b4(void *, int, int);
extern void func_ov002_0220a374(void *, int);

typedef struct UnkStruct_0229a870 {
    unsigned char pad_00[0x98];
    unsigned short unk_98;
    unsigned char pad_9A[0xab - 0x9a];
    unsigned char unk_AB;
    unsigned char pad_AC[0x6bc - 0xac];
    unsigned int unk_6BC;
} UnkStruct_0229a870;

void func_ov120_0229a870(UnkStruct_0229a870 *self)
{
    int a;
    int b;

    if (func_ov120_0229a448(self, 8) == 0) {
        if (self->unk_AB == 8) {
            self->unk_AB = 0;
        }
    }

    a = func_ov120_0229a81c(self);
    b = func_ov120_0229a7cc(self);
    func_ov002_0220a0b4(&self->unk_6BC, a, b);

    if (self->unk_AB >= 2 && self->unk_AB <= 7) {
        func_ov120_0229abdc(self, self->unk_98 & ~0xf);
    }

    func_ov002_0220a374(&self->unk_6BC, 1);
    func_ov120_0229a6d0(self);
}
