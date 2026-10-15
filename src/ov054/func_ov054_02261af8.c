/* func_ov054_02261af8 @ 0x02261af8, 0xbc bytes, Thumb, module ov054
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fc6c(void);
extern int func_0206f83c(void);
extern void func_02015fb0(void *, int, int, int, int, int);
extern int func_02015330(void *, void *, int, int, int);
extern void func_ov054_02261cc4(void *, int);
extern int func_020984e8(void);
extern int func_020992fc(int);
extern int func_020983e0(void);
extern void func_020983c8(int);
extern void func_0206844c(void *, unsigned char *, unsigned int);
extern int func_020155cc(void *);

typedef struct {
    unsigned int a;
    unsigned int b;
    unsigned int c;
} DataEntry;

extern DataEntry data_ov054_02262fac[];

struct UnkStruct_02261af8 {
    unsigned char pad_00[0x40];
    void *unk_40;
    unsigned char pad_44[0x6c];
    unsigned char *unk_B0;
    unsigned char pad_B4[0x10];
    int unk_C4;
};

void func_ov054_02261af8(struct UnkStruct_02261af8 *self)
{
    void *p40;
    unsigned int value;
    int r;
    unsigned char state;
    unsigned char buf[4];

    p40 = self->unk_40;
    value = data_ov054_02262fac[*(unsigned int *) (self->unk_B0 + 0x808)].a;

    if (func_0206fc6c() != 0) {
        r = func_0206f83c();
        func_02015fb0(self, r, 7, 10, 0, 0);
        if (r >= 0x1388) {
            state = 0x1d;
        } else {
            state = 0x1e;
        }
        *(unsigned short *) (buf + 2) = 0x149b;
        func_02015330(self, buf + 2, 0, 5, 1);
        func_ov054_02261cc4(self, 10);
        func_020992fc((int) func_020984e8());
        self->unk_C4 = func_020983e0();
        func_020983c8(self->unk_C4 + r);
    } else {
        state = 0x1c;
        func_020155cc(self);
        func_ov054_02261cc4(self, 0);
    }

    buf[0] = state;
    func_0206844c(p40, buf, value);
}
