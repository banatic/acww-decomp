/* func_020babb4 @ 0x020babb4, 0x190 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209def4(void *);
extern void func_02001b34(int);
extern void func_02001b44(int);
extern void func_02001bb4(int);
extern void func_02001da0(int);
extern void func_02001d1c(int);
extern void func_02001cc4(int, int, int, int);

extern struct {
    char pad0[0x1c];
    int idx;
    char pad1[0x1c];
    unsigned short w3c;
    unsigned short w3e;
} data_021f8ab0;

extern int data_021f8ac4[];
extern unsigned char data_021fba88[];

extern struct {
    char pad[4];
    unsigned short f4;
} data_021f7270;

extern struct {
    int pad;
    int idx;
} data_021f75b0;

typedef struct {
    unsigned int unk_00;
    unsigned int unk_04;
    short unk_08;
    unsigned char pad[0x8f6];
} E_t;

extern E_t data_021f75b8[];

typedef struct {
    unsigned char unk_00;
    unsigned char type;
    unsigned short a;
    unsigned short b;
} UnkStruct_020babb4;

void func_020babb4(void)
{
    int r4;
    int r5;
    UnkStruct_020babb4 tmp;
    E_t *e;

    r4 = data_021f8ac4[data_021f8ab0.idx];

    tmp.a = data_021f7270.f4;
    *(volatile unsigned short *) 0x05000400 = tmp.a;
    tmp.b = data_021f7270.f4;
    *(volatile unsigned short *) 0x05000000 = tmp.b;

    e = &data_021f75b8[data_021f75b0.idx];
    *(volatile unsigned short *) 0x04000030 = e->unk_08;
    *(volatile unsigned int *) 0x04000038 = e->unk_00;
    *(volatile unsigned int *) 0x0400003c = e->unk_04;

    func_0209def4(&tmp);

    if (tmp.type >= 6 && tmp.type < 0x12) {
        volatile unsigned int *p = (volatile unsigned int *) 0x04000000;
        *p = *p & ~0x200;
        func_02001b34(2);
    } else {
        unsigned int reg = *(volatile unsigned int *) 0x04000000;
        reg |= 0x200;
        *(volatile unsigned int *) 0x04000000 = reg;
        func_02001b44(2);
    }

    if (r4 > 0xa8) {
        volatile unsigned int *p = (volatile unsigned int *) 0x04000000;
        *p = *p & ~0xa00;
        func_02001b34(0xa);
        *(volatile unsigned short *) 0x04000050 = 0x2040;
    } else {
        unsigned int reg = *(volatile unsigned int *) 0x04000000;
        reg |= 0x800;
        *(volatile unsigned int *) 0x04000000 = reg;
        func_02001b44(8);
        if (r4 > 0x97) {
            volatile unsigned int *p = (volatile unsigned int *) 0x04000000;
            *p = *p & ~0x200;
            func_02001b34(2);
            *(volatile unsigned short *) 0x04000050 = 0x2048;
        } else {
            if (data_021fba88[0x11]) {
                *(volatile unsigned short *) 0x04000050 = 0x2040;
            } else {
                *(volatile unsigned short *) 0x04000050 = 0x2042;
            }
        }
    }

    r5 = 0xc0 - r4;
    if (r5 < 0) {
        r5 = 0;
    } else if (r5 > 0xc0) {
        r5 = 0xc0;
    }

    {
        unsigned int sum = (unsigned short) (r4 + data_021f8ab0.w3e);
        if (sum > 0x100) {
            sum = 0x100;
        }
        *(volatile unsigned short *) 0x04000016 = sum;
    }

    *(volatile unsigned short *) 0x04000014 = data_021f8ab0.w3c;

    func_02001bb4(1);
    func_02001da0(0x15);
    func_02001d1c(0x1f);
    func_02001cc4(0, r5, 0xff, 0xc0);
}