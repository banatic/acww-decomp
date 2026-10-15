/* func_ov073_02278ac4 @ 0x02278ac4, 0x1e0 bytes, Thumb, module ov073
 * mwccarm 1.2/base -O4,s
 */

typedef struct Msg {
    unsigned char code;
    unsigned char pad_01;
    unsigned short a;
    unsigned short b;
    unsigned short c;
} Msg;

typedef struct UnkStruct_02278ac4 {
    char pad_00[0x1e];
    unsigned char unk_1E;
    char pad_1F[0x40 - 0x1f];
    int unk_40;
    char pad_44[0xb4 - 0x44];
    int unk_B4;
    char pad_B8[0xc0 - 0xb8];
    int unk_C0;
    char pad_C4[0xc8 - 0xc4];
    unsigned char unk_C8;
} UnkStruct_02278ac4;

extern int data_ov073_02279a10;
extern int data_021f3b0c;
extern int data_021dc7a8;

extern int func_020160b4(void *argument0);
extern int func_020ab504(void *argument0);
extern int func_020874c4(int *p);
extern void func_02015fb0(UnkStruct_02278ac4 *self, int a, int b, int c, int d, int e);
extern int func_02099fe8(void);
extern int func_0201b43c(int a, int b);
extern int func_ov073_02278d94(UnkStruct_02278ac4 *self);
extern void func_0201b420(int a, int b);
extern int func_020154b4(UnkStruct_02278ac4 *self, unsigned short *p, int a, int b, int c);
extern int func_0209f150(int *p, int a);
extern void func_0208b520(void);
extern int func_0209a000(unsigned short *p, int a);
extern void func_0209f128(int *p, int a);
extern void func_0206844c(int a, Msg *m, int *t);

void func_ov073_02278ac4(UnkStruct_02278ac4 *self)
{
    Msg m;
    int r;
    int n;
    int status;
    int *tail;

    r = func_020ab504((void *) func_020160b4(self));
    tail = &data_ov073_02279a10;
    status = 0xff;
    switch (self->unk_1E) {
        case 1:
            if (r == 0) {
                status = 6;
            } else {
                status = 2;
            }
            break;
        case 3:
            if (r == 0) {
                func_02015fb0(self, func_020874c4(&data_021f3b0c), 0, 0xa, 0, 0);
                status = 0x10;
            } else if (r == 1) {
                status = 0x17;
            }
            break;
        case 8:
            if (r == 0) {
                status = 9;
            }
            break;
        case 0xa:
            if (r == 0) {
                status = 0xb;
            }
            break;
        case 0xc:
            if (r == 0) {
                status = 0xd;
            }
            break;
        case 0x10:
            if (r == 0) {
                status = 0x12;
            } else if (r == 1) {
                status = 7;
            }
            break;
        case 0x13:
            if (r == 0) {
                n = func_02099fe8();
                if (func_0201b43c(self->unk_B4, self->unk_C0) == 0) {
                    status = 0x1b;
                } else if (n < 0) {
                    status = 0x1c;
                } else if (func_ov073_02278d94(self) == 0) {
                    status = 0x14;
                } else {
                    func_0201b420(self->unk_B4, self->unk_C0);
                    m.a = 0x1531;
                    func_020154b4(self, &m.a, 0, 5, 0);
                    self->unk_C8 = 0;
                    status = 0x15;
                }
            }
            break;
        case 0x17:
            if (r == 0) {
                if (func_0209f150(&data_021dc7a8, 4) != 0) {
                    status = 0x18;
                } else {
                    func_0208b520();
                    status = 0x19;
                }
            }
            break;
        case 0x19:
            if (r == 0) {
                if (func_0201b43c(self->unk_B4, 0x3e8) == 0) {
                    status = 0x1b;
                } else {
                    m.b = 0x1567;
                    if (func_0209a000(&m.b, 0) != 0) {
                        status = 0x15;
                        func_0201b420(self->unk_B4, 0x3e8);
                        func_0209f128(&data_021dc7a8, 4);
                        self->unk_C8 = 1;
                        m.c = 0x1567;
                        func_020154b4(self, &m.c, 0, 5, 0);
                    } else {
                        status = 0x1c;
                    }
                }
            }
            break;
    }
    if (status != 0xff) {
        m.code = (unsigned char) status;
        func_0206844c(self->unk_40, &m, tail);
    }
}
