/* func_0200ae7c @ 0x0200ae7c, 0x39c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct T12c {
    unsigned char pad_00[4];
    int unk_04;
    int unk_08;
} T12c;

typedef struct UnkStruct_0200ae7c {
    u8 pad_00[0xec];
    u8 sub_ec[0x10a - 0xec];
    u8 unk_10A;
    u8 pad_10B[0x12c - 0x10b];
    T12c *unk_12C;
    u8 pad_130[0x2d0 - 0x130];
    u8 sub_2d0[0x2e0 - 0x2d0];
    int unk_2E0;
    u8 pad_2E4[0x5a0 - 0x2e4];
    u8 sub_5a0[0x7f0 - 0x5a0];
    int unk_7F0;
    u8 pad_7F4[0x7fc - 0x7f4];
    int unk_7FC;
    int unk_800;
    u8 pad_804[0x810 - 0x804];
    int unk_810;
    u8 pad_814[0x81c - 0x814];
    int unk_81C;
    u16 unk_820;
} UnkStruct_0200ae7c;

extern int data_020d83a4;
extern int data_020d83b4;

extern int func_02056f94(void *p);
extern int func_02096e38(void);
extern int func_0203e1c4(void);
extern void func_020109fc(UnkStruct_0200ae7c *self, int a, int b, int c);
extern int func_0200fbe0(UnkStruct_0200ae7c *self);
extern void func_0205eae0(void *p, int a, int b, int c);
extern void func_0203ee14(UnkStruct_0200ae7c *self, void *b);
extern void func_0203ee08(UnkStruct_0200ae7c *self, void *b);
extern unsigned int *func_0200f27c(UnkStruct_0200ae7c *self, int a);
extern void func_0200f268(UnkStruct_0200ae7c *self, int a);
extern void func_020a8164(void *p, void *g);
extern int func_0203e190(void);
extern int func_0209a110(u16 *p);
extern int func_0206f6d4(int a);
extern int func_0206fbc0(void);
extern int func_0206fc6c(void);
extern int func_02043540(int a, int b);
extern int func_0203e19c(void);
extern int func_02008258(UnkStruct_0200ae7c *self, int a);
extern int func_0200d4e8(UnkStruct_0200ae7c *self, int a, int b, int c);

void func_0200ae7c(UnkStruct_0200ae7c *self, u8 *state, int cond)
{
    void *b;
    int r;
    int n;
    u16 v[2];

    switch (*state) {
        case 0:
            if (func_02056f94(self->sub_2d0) == 0) {
                break;
            }
            if (self->unk_820 == 0x1520) {
                if (func_02096e38() != 0) {
                    *state = 6;
                    break;
                }
                if (func_0203e1c4() == 0) {
                    break;
                }
                func_020109fc(self, 0x6c, 0, 0);
                r = func_0200fbe0(self);
                if (r == 4) {
                    func_0205eae0(self->sub_5a0, 0, 9, 0);
                } else if (r == 3) {
                    func_0205eae0(self->sub_5a0, 0x13, 3, 0);
                }
                *state = 7;
                b = self;
                if (self != 0) {
                    b = (char *) self + 0xec;
                }
                func_0203ee14(self, b);
                func_0200f27c(self, 0x11);
                func_020a8164((char *) self + 0xec, &data_020d83a4);
                self->unk_10A = 0x12;
                self->unk_12C->unk_08 = 1;
                break;
            }
            if (cond != 0) {
                if (func_0203e190() == 0 && func_0203e1c4() == 0) {
                    break;
                }
                func_020109fc(self, 0x6c, 0, 0);
                r = func_0200fbe0(self);
                if (r == 4) {
                    func_0205eae0(self->sub_5a0, 0, 9, 0);
                } else if (r == 3) {
                    func_0205eae0(self->sub_5a0, 0x13, 3, 0);
                }
                *state = 1;
                b = self;
                if (self != 0) {
                    b = (char *) self + 0xec;
                }
                func_0203ee14(self, b);
                func_0200f27c(self, 0x11);
                func_020a8164((char *) self + 0xec, &data_020d83b4);
                self->unk_10A = 2;
                self->unk_12C->unk_08 = 1;
                break;
            }
            v[1] = self->unk_820;
            func_0209a110(&v[1]);
            *state = 6;
            break;
        case 1:
            if (self->unk_12C == 0) {
                break;
            }
            if (self->unk_12C->unk_04 == 0) {
                break;
            }
            *state = 2;
            self->unk_81C = 3;
            break;
        case 2:
            n = self->unk_81C;
            if (n >= 0xf) {
                *state = 3;
            } else {
                if (self->unk_12C == 0) {
                    break;
                }
                if (self->unk_12C->unk_04 != 0) {
                    break;
                }
                if (n == 5) {
                    if (func_0206f6d4(self->unk_820) == 0) {
                        break;
                    }
                    self->unk_81C = 6;
                    break;
                }
                if (n != 6) {
                    break;
                }
                if (func_0206fbc0() == 0) {
                    break;
                }
                self->unk_81C = 0xf;
                self->unk_2E0 = 0x1000;
                if (func_0206fc6c() != 0) {
                    *state = 6;
                    b = self;
                    if (self != 0) {
                        b = (char *) self + 0xec;
                    }
                    func_0203ee08(self, b);
                    func_0200f268(self, 0x11);
                    func_0203e19c();
                    break;
                }
                *state = 3;
            }
            // fall through
        case 3:
            if (self->unk_810 != -1) {
                break;
            }
            self->unk_810 = func_02043540(self->unk_800, self->unk_820);
            if (self->unk_810 == -1) {
                break;
            }
            func_020109fc(self, 0, 6, 6);
            *state = 4;
            if (func_0200fbe0(self) == 4) {
                func_0205eae0(self->sub_5a0, 0, 9, 0);
            }
            break;
        case 4:
            if (self->unk_810 != -1) {
                break;
            }
            *state = 5;
            // fall through
        case 5:
            if (self->unk_12C == 0) {
                break;
            }
            if (self->unk_12C->unk_04 != 0) {
                break;
            }
            b = self;
            if (self != 0) {
                b = (char *) self + 0xec;
            }
            func_0203ee08(self, b);
            func_0200f268(self, 0x11);
            func_0203e19c();
            *state = 6;
            func_020109fc(self, 0, 6, 6);
            if (func_0200fbe0(self) == 4) {
                func_0205eae0(self->sub_5a0, 0, 9, 0);
            }
            break;
        case 6:
            self->unk_7FC = func_02008258(self, self->unk_7F0);
            func_0200d4e8(self, 3, 1, -1);
            func_0200f268(self, 0xd);
            self->unk_81C = 0xf;
            break;
        case 7:
            if (self->unk_12C == 0) {
                break;
            }
            if (self->unk_12C->unk_04 == 0) {
                break;
            }
            *state = 8;
            break;
        case 8:
            if (self->unk_12C == 0) {
                break;
            }
            if (self->unk_12C->unk_04 != 0) {
                break;
            }
            *state = 3;
            if (self->unk_810 != -1) {
                break;
            }
            self->unk_810 = func_02043540(self->unk_800, self->unk_820);
            if (self->unk_810 == -1) {
                break;
            }
            *state = 5;
            func_020109fc(self, 0, 6, 6);
            if (func_0200fbe0(self) == 4) {
                func_0205eae0(self->sub_5a0, 0, 9, 0);
            }
            break;
    }
}
