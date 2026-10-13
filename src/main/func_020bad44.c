/* func_020bad44 @ 0x020bad44, 0x11c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209def4(void *);
extern int func_0206fea4(void);
extern void func_02001afc(unsigned char mask);
extern void func_02001b0c(int arg);

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
    unsigned short f6;
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
} UnkStruct_020bad44;

void func_020bad44(void)
{
    int r4;
    UnkStruct_020bad44 tmp;
    E_t *e;

    r4 = data_021f8ac4[data_021f8ab0.idx];

    tmp.a = data_021f7270.f4;
    *(volatile unsigned short *) 0x05000400 = tmp.a;
    tmp.b = data_021f7270.f6;
    *(volatile unsigned short *) 0x05000000 = tmp.b;

    e = &data_021f75b8[data_021f75b0.idx];
    *(volatile unsigned short *) 0x04001030 = e->unk_08;
    *(volatile unsigned int *) 0x04001038 = e->unk_00;
    *(volatile unsigned int *) 0x0400103c = e->unk_04;

    func_0209def4(&tmp);

    if (tmp.type >= 6 && tmp.type < 0x12) {
        volatile unsigned int *p = (volatile unsigned int *) 0x04001000;
        *p = *p & ~0x200;
        if (func_0206fea4() == 0) {
            func_02001afc(2);
        }
    } else {
        unsigned int reg = *(volatile unsigned int *) 0x04001000;
        reg |= 0x200;
        *(volatile unsigned int *) 0x04001000 = reg;
        if (func_0206fea4() == 0) {
            func_02001b0c(2);
        }
    }

    if (data_021fba88[0x11]) {
        *(volatile unsigned short *) 0x04001050 = 0x2040;
    } else {
        *(volatile unsigned short *) 0x04001050 = 0x2042;
    }

    {
        unsigned int sum = (unsigned short) (r4 + data_021f8ab0.w3e);
        if (sum > 0x100) {
            sum = 0x100;
        }
        *(volatile unsigned short *) 0x04001016 = sum;
    }

    *(volatile unsigned short *) 0x04001014 = data_021f8ab0.w3c;
}
