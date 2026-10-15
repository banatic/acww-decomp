/* func_0202a7cc @ 0x0202a7cc, 0xd8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0202a7cc {
    unsigned char pad_00[0x40];
    void *unk_40;
    unsigned char pad_44[0x6c];
    void (UnkStruct_0202a7cc::*callback)(int *);
    unsigned char pad_B8[0x48];
    unsigned char *unk_100;
    unsigned char pad_104[0x28];
    int unk_12C;
};

struct UnkStruct_0202a7cc_2 {
    unsigned char unk_00;
    int unk_04;
    unsigned char unk_08;
};

extern "C" {
int func_0206fc6c(void);
void func_0202da88(UnkStruct_0202a7cc *self, void *ptr);
int func_02081edc(void *object);
int func_0206fc44(void);
void func_02081c14(int a, int b, int c);
int func_020984e8(void);
int func_02099870(int value);
int func_020802a4(int a, int b, int c, int d);
void *func_02094fd4(void *ptr);
void func_02081c94(int a, void *ptr);
void func_02068404(void *a, int b, void *c);
void *func_02094fbc(void *ptr);
void func_0206844c(void *a, void *b, int c);
}

extern unsigned char data_021c27dc[];

extern "C" void func_0202a7cc(UnkStruct_0202a7cc *self)
{
    UnkStruct_0202a7cc_2 local;
    unsigned char big[0x24];

    if (func_0206fc6c() != 0) {
        int r4 = *(int *) (self->unk_100 + 0x830);
        func_0202da88(self, (void *) data_021c27dc);

        if (self->unk_12C != 0 && func_02081edc((void *) self->unk_12C) != 0) {
            int tmp = func_0206fc44();
            func_02081c14(self->unk_12C, tmp, 6);
        } else {
            int tmp2 = func_0206fc44();
            int tmp3 = func_02099870(func_020984e8());
            self->unk_12C = func_020802a4(r4, tmp2, 6, tmp3);
        }

        if (self->unk_12C != 0) {
            func_02094fd4(big);
            func_02081c94(self->unk_12C, big);
            func_02068404(self->unk_40, 0, big);
            func_02094fbc(big);
        }
    }

    if (self->callback != 0) {
        (self->*self->callback)(&local.unk_04);
    }
    local.unk_00 = local.unk_08;
    func_0206844c(self->unk_40, &local, local.unk_04);
}
