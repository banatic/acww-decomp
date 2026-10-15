/* func_ov120_0229b7f8 @ 0x0229b7f8, 0xd8 bytes, Thumb, module ov120
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208014(void);
extern void func_ov120_0229b64c(void *self);
extern int func_ov002_02208008(void *self);
extern int func_ov120_0229a584(void *self, int val);
extern int func_ov120_0229a448(void *self, int num);
extern void func_ov120_0229abdc(void *self, unsigned int val);
extern void func_ov120_0229a730(void *self);
extern void func_ov120_0229a710(void *self);
extern void func_ov120_0229adc4(void *self, int num);
extern void func_ov120_0229ad5c(void *self, int num);
extern void func_ov120_0229a45c(void *self);
extern unsigned char func_ov120_0229ae78(void *self, unsigned char a, unsigned char b);
extern void func_ov120_0229a438(void *self, unsigned int val);
extern unsigned char *func_ov002_02208098(void *self, unsigned char value);
extern unsigned short data_021fbe40[];

typedef struct UnkStruct_0229b7f8 {
    unsigned char pad_00[0x98];
    unsigned short unk_98;
    unsigned char pad_9A[0x11];
    unsigned char unk_AB;
    unsigned char unk_AC;
    unsigned char unk_AD;
    unsigned char unk_AE;
} UnkStruct_0229b7f8;

void func_ov120_0229b7f8(UnkStruct_0229b7f8 *self)
{
    if (func_ov002_02208014() != 0) {
        func_ov120_0229b64c(self);
        return;
    }
    if (func_ov120_0229a584(self, func_ov002_02208008(self)) != 0) {
        if (func_ov120_0229a448(self, 8) != 0) {
            if (self->unk_AB >= 2 && self->unk_AB <= 7) {
                func_ov120_0229abdc(self, self->unk_98 & ~0xf);
            }
        }
        func_ov120_0229a730(self);
    } else {
        unsigned short cur = data_021fbe40[1];
        if (cur & 1) {
            func_ov120_0229a710(self);
            return;
        }
        if (!(cur & 0x800)) {
            return;
        }
        func_ov120_0229adc4(self, 0);
        func_ov120_0229ad5c(self, 0xe);
        if (self->unk_AB >= 2 && self->unk_AB <= 7) {
            func_ov120_0229a45c(self);
        }
        self->unk_AC = func_ov120_0229ae78(self, self->unk_AD, self->unk_AE);
        func_ov120_0229a438(self, 0x800);
        func_ov002_02208098(self, 9);
        func_ov120_0229a730(self);
    }
}
