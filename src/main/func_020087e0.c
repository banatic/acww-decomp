/* func_020087e0 @ 0x020087e0, 0x118 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct T12c {
    unsigned char pad_00[4];
    int unk_04;
    int unk_08;
} T12c;

struct UnkStruct_020087e0 {
    unsigned char pad_00[0xec];
    unsigned char pad_EC[0x10a - 0xec];
    unsigned char unk_10A;
    unsigned char pad_10B[0x12c - 0x10a - 1];
    T12c *unk_12C;
    unsigned char pad_130[0x7d5 - 0x12c - 4];
    unsigned char unk_7D5;
    unsigned char pad_7D6[0x7f0 - 0x7d5 - 1];
    int unk_7F0;
    unsigned char pad_7F4[0x7fc - 0x7f4];
    int unk_7FC;
    int unk_800;
};

extern void *data_020ccf94;
extern int data_020d83a4;

extern int func_02073908(void *a, int b);
extern int func_0203e1c4(void);
extern void func_0203ee14(void *self, void *b);
extern unsigned int *func_0200f27c(void *self, int code);
extern void func_020a8164(void *p, void *g);
extern void func_0202f17c(void);
extern unsigned char func_02008258(void *arg0, int index);
extern int func_0200d4e8(void *self, int a, int b, int c);
extern void func_0203ee08(void *self, void *b);
extern void func_0200f268(void *self, int code);
extern int func_0203e19c(void);

void func_020087e0(struct UnkStruct_020087e0 *self)
{
    void *b;
    unsigned char *statep;

    if (func_02073908(data_020ccf94, self->unk_800) != 0) {
        statep = &self->unk_7D5;
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
                    func_020a8164((char *) self + 0xec, &data_020d83a4);
                    self->unk_10A = 0x1e;
                    self->unk_12C->unk_08 = 1;
                    func_0202f17c();
                } else {
                    self->unk_7FC = func_02008258(self, self->unk_7F0);
                    func_0200d4e8(self, 3, 1, -1);
                }
                break;
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
                }
                break;
        }
    } else {
        self->unk_7FC = func_02008258(self, self->unk_7F0);
    }
}
