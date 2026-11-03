/* local_host_3: 6 functions, module ov066
 * mwccarm 1.2/base -O4,p
 * func_ov066_02268c4c @ 0x02268c4c, 0x44 bytes, ARM
 * func_ov066_02268c18 @ 0x02268c18, 0x34 bytes, ARM
 * func_ov066_02268be4 @ 0x02268be4, 0x34 bytes, ARM
 * func_ov066_02268b04 @ 0x02268b04, 0xe0 bytes, ARM
 * func_ov066_02268ad0 @ 0x02268ad0, 0x34 bytes, ARM
 * func_ov066_02268a60 @ 0x02268a60, 0x70 bytes, ARM
 */

#include "types.h"

typedef struct Pkt {
    u16 unk_00;
    u16 err; // 0x02
    unsigned char pad_04[4];
    u16 kind; // 0x08
} Pkt;

typedef struct UnkStruct_02268b04 {
    unsigned char pad_00[0xc0];
    u32 b0 : 2;   // 0xc0, bits 0..1
    int flag : 1; // bit 2
    u32 rest : 29;
} UnkStruct_02268b04;

typedef struct UnkStruct_02268a60_2 {
    char pad_00[2];
    unsigned short unk_02;
} UnkStruct_02268a60_2;

typedef struct UnkStruct_02268a60 {
    char pad_00[0xc0];
    int : 3;
    int b : 1;
} UnkStruct_02268a60;

extern int WM_SetParentParameter(void (*func)(void *), int data);
extern void func_ov066_0226686c(int status);
extern int *data_ov066_0226bdf4;
extern int WM_StartParent(void (*)(void *));
int func_ov066_02266e08(void);
extern void func_ov066_02269154(void *p);
void func_ov066_0226908c(Pkt *p);
void func_ov066_02266e64(void);
void func_ov066_02268f98(Pkt *p);
extern int WM_EndParent(void (*)(void *));
extern int *data_ov066_0226bdec;
extern void func_ov066_02269dcc(void);
extern void func_ov066_02266bf4(void);

void func_ov066_02268c18(unsigned short *arg0);
void func_ov066_02268be4(void);
void func_ov066_02268b04(Pkt *p);
void func_ov066_02268a60(UnkStruct_02268a60_2 *self);

void func_ov066_02268c4c(void)
{
    int status = WM_SetParentParameter((void (*)(void *)) func_ov066_02268c18, *data_ov066_0226bdf4);
    if (status == 2) {
        return;
    }
    func_ov066_0226686c(status);
}

void func_ov066_02268c18(unsigned short *arg0)
{
    if (arg0[1] == 0) {
        func_ov066_02268be4();
    } else {
        func_ov066_0226686c(arg0[1]);
    }
}

void func_ov066_02268be4(void)
{
    int status = WM_StartParent((void (*)(void *)) (void (*)(void *)) func_ov066_02268b04);
    if (status == 2) {
        return;
    }
    func_ov066_0226686c(status);
}

void func_ov066_02268b04(Pkt *p)
{
    if (func_ov066_02266e08() != 0) {
        return;
    }
    if (p->err == 0) {
        switch (p->kind) {
            case 0:
                break;
            case 2:
                func_ov066_02269154(p);
                break;
            case 7:
                func_ov066_0226908c(p);
                break;
            case 9:
                if ((*(UnkStruct_02268b04 * *) &data_ov066_0226bdf4)->flag) {
                    func_ov066_02266e64();
                } else {
                    func_ov066_02268f98(p);
                }
                break;
        }
    } else {
        func_ov066_0226686c((u16) p->err);
    }
}

void func_ov066_02268ad0(void)
{
    int status = WM_EndParent((void (*)(void *)) (void (*)(void *)) func_ov066_02268a60);
    if (status == 2) {
        return;
    }
    func_ov066_0226686c(status);
}

void func_ov066_02268a60(UnkStruct_02268a60_2 *self)
{
    if (func_ov066_02266e08() != 0) {
        return;
    }
    if (self->unk_02 == 0) {
        *(data_ov066_0226bdec + 1) = 4;
        if ((*(UnkStruct_02268a60 * *) &data_ov066_0226bdf4)->b) {
            func_ov066_02269dcc();
        }
        func_ov066_02266bf4();
        return;
    } else {
        func_ov066_0226686c(self->unk_02);
        return;
    }
}
