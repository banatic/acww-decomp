/* func_02008aa8 @ 0x02008aa8, 0x140 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct T12c {
    unsigned char pad_00[4];
    int unk_04;
    int unk_08;
} T12c;

struct UnkStruct_02008aa8 {
    unsigned char pad_00[0xec];
    unsigned char pad_EC[0x10a - 0xec];
    unsigned char unk_10A;
    unsigned char pad_10B[0x12c - 0x10a - 1];
    T12c *unk_12C;
    unsigned char pad_130[0x704 - 0x130];
    int unk_704;
    unsigned char pad_708[0x7d4 - 0x708];
    unsigned char unk_7D4;
    unsigned char unk_7D5;
    unsigned char pad_7D6[0x7f0 - 0x7d6];
    int unk_7F0;
    unsigned char pad_7F4[0x7fc - 0x7f4];
    int unk_7FC;
    int unk_800;
};

extern void *data_020ccf94;
extern int data_020d83b4;

extern int func_02056f94(void *p);
extern void func_020109fc(void *self, int a, int b, int c);
extern int func_02073908(void *a, int b);
extern unsigned char func_02008258(void *self, int idx);
extern int func_0200faf0(void *self, int code);
extern int func_0203e1c4(void);
extern void func_0203ee14(void *self, void *b);
extern unsigned int *func_0200f27c(void *self, int code);
extern void func_020a8164(void *p, void *g);
extern void func_0203ae98(void);
extern void func_0203ee08(void *self, void *b);
extern void func_0200f268(void *self, int code);
extern int func_0203e19c(void);
extern int func_0200d4e8(void *self, int a, int b, int c);
extern int func_0203b144(void);
extern void func_02035624(int code);

void func_02008aa8(struct UnkStruct_02008aa8 *self)
{
    unsigned char *statep = &self->unk_7D4;
    void *b;

    if (self->unk_704 == 0x76) {
        if (func_02056f94((char *) self + 0x2d0) != 0) {
            func_020109fc(self, 0x77, 0, 0);
            if (func_02073908(data_020ccf94, self->unk_800) == 0) {
                *statep = 3;
                self->unk_7FC = func_02008258(self, self->unk_7F0);
            }
        }
    } else {
        func_0200faf0(self, 0x400);
        switch (*statep) {
            case 0:
                if (func_0203e1c4() != 0) {
                    *statep = 1;
                    b = (char *) self;
                    if (self != 0) {
                        b = (char *) self + 0xec;
                    }
                    func_0203ee14(self, b);
                    func_0200f27c(self, 0x11);
                    func_020a8164((char *) self + 0xec, &data_020d83b4);
                    self->unk_10A = 0x15;
                    self->unk_12C->unk_08 = 1;
                    func_0203ae98();
                }
                // fall through
            case 1:
                if (self->unk_12C != 0 && self->unk_12C->unk_04 != 0) {
                    *statep = 2;
                }
                break;
            case 2:
                if (self->unk_12C != 0 && self->unk_12C->unk_04 == 0) {
                    b = (char *) self;
                    if (self != 0) {
                        b = (char *) self + 0xec;
                    }
                    func_0203ee08(self, b);
                    func_0200f268(self, 0x11);
                    func_0203e19c();
                    self->unk_7FC = func_02008258(self, self->unk_7F0);
                    func_0200d4e8(self, 3, 1, -1);
                    func_0200f268(self, 8);
                    func_0203b144();
                    func_02035624(0xc);
                }
                break;
        }
    }
}
