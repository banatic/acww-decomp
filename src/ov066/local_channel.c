/* local_channel: 4 functions, module ov066
 * mwccarm 1.2/base -O4,p
 * func_ov066_0226a160 @ 0x0226a160, 0x50 bytes, ARM
 * func_ov066_0226a074 @ 0x0226a074, 0xec bytes, ARM
 * func_ov066_0226a00c @ 0x0226a00c, 0x68 bytes, ARM
 * func_ov066_02269f6c @ 0x02269f6c, 0xa0 bytes, ARM
 */

#include "types.h"

typedef struct Pkt {
    u16 unk_00;
    u16 err; // 0x02
    unsigned char pad_04[4];
    u16 id;  // 0x08
    u16 seq; // 0x0a
} Pkt;

typedef struct Ctl {
    unsigned char pad_00[4];
    int state; // 0x04
    u8 unk_08; // 0x08
} Ctl;

typedef struct UnkStruct_0226a074 {
    unsigned char pad_00[0xc0];
    u32 lo7 : 7; // 0xc0 bits 0..6
    int b7 : 1;  // bit 7
    u32 hi : 24;
} UnkStruct_0226a074;

struct UnkStruct_0226a00c {
    int pad_00;
    int unk_04;
};

struct UnkStruct_0226a00c_2 {
    char pad_00[0x8d];
    char unk_8D;
};

extern void func_ov066_0226686c(int status);
extern int WM_MeasureChannel(void (*f)(void *), int a, int b, int c, int d);
extern u16 data_ov066_0226be04;
extern u8 data_ov066_0226bdfc;
extern u16 data_ov066_0226be00;
extern Ctl *data_ov066_0226bdec;
extern UnkStruct_0226a074 *data_ov066_0226bdf4;
void func_ov066_02266bf4(void);
extern struct UnkStruct_0226a00c;
extern struct UnkStruct_0226a00c_2;
extern unsigned int func_ov066_0226a278(unsigned int argument0);
extern unsigned int func_ov066_022699ec(void);

void func_ov066_0226a074(Pkt *p);
int func_ov066_02269f6c(unsigned int argument0);

int func_ov066_0226a160(int param)
{
    int status = WM_MeasureChannel((void (*)(void *))(void (*)(void *)) func_ov066_0226a074, 3, 17, param, 30);
    if (status == 2) {
        return 1;
    }
    func_ov066_0226686c(status);
    return 0;
}

void func_ov066_0226a074(Pkt *p)
{
    u16 seq;
    u16 id;
    if (p->err == 0) {
        seq = p->seq;
        id = p->id;
        if (data_ov066_0226be04 > seq) {
            data_ov066_0226be04 = seq;
            data_ov066_0226be00 = (u16) (1 << (id - 1));
            data_ov066_0226bdfc = 1;
        } else if (data_ov066_0226be04 == seq) {
            data_ov066_0226be00 = (u16) (data_ov066_0226be00 | (1 << (id - 1)));
            data_ov066_0226bdfc = (u8) (data_ov066_0226bdfc + 1);
        }
        if (func_ov066_02269f6c((u16) id) != 0) {
            data_ov066_0226bdec->state = 4;
            if (data_ov066_0226bdec->unk_08 == 0xfe) {
                data_ov066_0226bdf4->b7 = 0;
            }
            func_ov066_02266bf4();
        }
    } else {
        func_ov066_0226686c((u16) p->err);
    }
}

void func_ov066_0226a00c(void)
{
    struct UnkStruct_0226a00c_2 *p;
    (*(struct UnkStruct_0226a00c **) &data_ov066_0226bdec)->unk_04 = 5;
    (*(char *) &data_ov066_0226bdfc) = 0;
    (*(short *) &data_ov066_0226be00) = 0;
    (*(short *) &data_ov066_0226be04) = 0x65;
    p = (*(struct UnkStruct_0226a00c_2 **) &data_ov066_0226bdf4);
    p->unk_8D = 0;
    func_ov066_02269f6c(0);
}

int func_ov066_02269f6c(unsigned int argument0)
{
    unsigned short bits;
    unsigned char rem, i;

    if (func_ov066_0226a278(argument0) != 0) {
        goto ret0;
    }
    if ((*(unsigned char *) &data_ov066_0226bdfc) == 0) {
        goto ret0;
    }
    i = 0;
    rem = (unsigned char) (func_ov066_022699ec() % (*(unsigned char *) &data_ov066_0226bdfc));
    bits = (*(unsigned short *) &data_ov066_0226be00);
    do {
        if ((bits & (1U << i)) != 0) {
            if (rem != 0) {
                rem = (unsigned char) (rem - 1);
            } else {
                (*(unsigned char **) &data_ov066_0226bdf4)[0x8d] = (unsigned char) (i + 1);
                goto ret1;
            }
        }
        i = (unsigned char) (i + 1);
    } while (i < 14);
ret0:
    return 0;
ret1:
    return 1;
}
