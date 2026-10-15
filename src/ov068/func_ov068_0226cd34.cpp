/* func_ov068_0226cd34 @ 0x0226cd34, 0x114 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

struct Main;

struct UnkStruct_0226cd34 {
    char pad_00[8];
    void (Main::*pmf)(int);
};

struct Main {
    char pad_00[0x14];
    UnkStruct_0226cd34 *holder;
    char pad_18[0x20 - 0x18];
    int unk_20;
    int unk_24;
    char pad_28[0x2c - 0x28];
    short unk_2C;
    char pad_2E[0x34 - 0x2e];
    short unk_34;
    short unk_36;
    char pad_38[0x3a - 0x38];
    unsigned short unk_3A;
    char pad_3C[0xd8 - 0x3c];
    short unk_D8;
    short unk_DA;
    short unk_DC;
    short unk_DE;
    unsigned char unk_E0;
    char pad_E1[0xf4 - 0xe1];
    int unk_F4;
    int unk_F8;
};

extern "C" {
int func_ov068_0226c0a4(Main *);
int func_02014868(int);
}

extern "C" void func_ov068_0226cd34(Main *self, int arg)
{
    if (self->unk_E0 != 0) {
        if (func_ov068_0226c0a4(self) == 0) {
            self->unk_E0 = 0;
        }
    }

    if (self->holder) {
        (self->*self->holder->pmf)(arg);
    }

    if (self->unk_20 > 0) {
        self->unk_20--;
    }

    if (self->unk_D8 > 0) {
        self->unk_D8--;
    }
    if (self->unk_DA > 0) {
        self->unk_DA--;
    }
    if (self->unk_DC > 0) {
        self->unk_DC--;
    }
    if (self->unk_DE > 0) {
        self->unk_DE--;
    }

    if (self->unk_24 > 0) {
        self->unk_24--;
    }

    if (self->unk_3A != 0) {
        self->unk_3A--;
    }

    if (func_02014868(arg + 0x618) == 0) {
        if (self->unk_F4 > 0) {
            self->unk_F4--;
        } else if (self->unk_F8 > 0) {
            self->unk_F8--;
        }

        if (self->unk_34 > 0) {
            self->unk_34--;
        }
        if (self->unk_36 > 0) {
            self->unk_36--;
        }
    }

    if (self->unk_2C > 0) {
        self->unk_2C--;
    }
}
