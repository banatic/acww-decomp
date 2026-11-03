/* town_map_list: 4 functions, module ov120
 * mwccarm 1.2/base -O4,s
 * func_ov120_0229a9b4 @ 0x0229a9b4, 0x7c bytes, Thumb
 * func_ov120_0229a928 @ 0x0229a928, 0x8c bytes, Thumb
 * func_ov120_0229a904 @ 0x0229a904, 0x24 bytes, Thumb
 * func_ov120_0229a8e8 @ 0x0229a8e8, 0x1c bytes, Thumb
 */

typedef struct {
    char pad_00[0xa7];
    unsigned char unk_A7;
    char pad_A8;
    unsigned char unk_A9;
} SelfType;

extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;
extern int func_ov120_0229a448(void *, int);
extern void func_ov120_0229adc4(void *, int);
extern void func_ov120_0229b22c(void *);
extern void func_ov120_0229b214(void *);
extern void func_ov120_0229abec(void *, int);
extern void func_ov120_0229a438(SelfType *self, int param);
extern void func_ov120_0229ad5c(SelfType *self, unsigned char param);
extern void func_ov120_0229a428(void *p, int n);

int func_ov120_0229a9b4(unsigned char *a)
{
    unsigned char b0 = data_021f6c58;
    unsigned char b1 = data_021f6c54;
    if ((int) b1 < 0x38 || (int) b1 > 0x4c) {
        return 0;
    }
    if (func_ov120_0229a448(a, 1)) {
        if ((int) b0 < 0xcc || (int) b0 > 0xe4) {
            return 0;
        }
        func_ov120_0229adc4(a, 0);
        func_ov120_0229b22c(a);
    } else {
        if ((int) b0 < 0xb0 || (int) b0 > 0xc8) {
            return 0;
        }
        func_ov120_0229adc4(a, 0);
        func_ov120_0229b214(a);
    }
    func_ov120_0229abec(a, 0);
    a[0xa3] = 0xff;
    return 1;
}

void func_ov120_0229a928(SelfType *self)
{
    if (!func_ov120_0229a448((void *) self, 0x40)) {
        return;
    }

    if (self->unk_A7) {
        self->unk_A7--;
    }

    if (self->unk_A7 == 0) {
        if (func_ov120_0229a448((void *) self, 0x200) != 0) {
            func_ov120_0229a428((void *) self, 0x100);
        } else {
            func_ov120_0229ad5c(self, self->unk_A9);
        }
        self->unk_A7 = 0x0f;
    } else {
        if (self->unk_A7 == 5) {
            if (func_ov120_0229a448((void *) self, 0x200) != 0) {
                func_ov120_0229a438(self, 0x100);
            } else {
                func_ov120_0229ad5c(self, 0xe);
            }
        }
    }
}

void func_ov120_0229a904(void *p)
{
    func_ov120_0229a438((SelfType *) p, 0x40);
    func_ov120_0229a428(p, 0x100);
    ((unsigned char *) p)[0xa7] = 0xf;
}

void func_ov120_0229a8e8(void *p)
{
    func_ov120_0229a428(p, 0x40);
    func_ov120_0229a428(p, 0x100);
}
