/* local_wireless_5: 16 functions, module ov066
 * mwccarm 1.2/base -O4,p
 * func_ov066_02267348 @ 0x02267348, 0xbc bytes, ARM
 * func_ov066_022672b8 @ 0x022672b8, 0x90 bytes, ARM
 * func_ov066_0226727c @ 0x0226727c, 0x3c bytes, ARM
 * func_ov066_02267224 @ 0x02267224, 0x58 bytes, ARM
 * func_ov066_02267188 @ 0x02267188, 0x9c bytes, ARM
 * func_ov066_02267138 @ 0x02267138, 0x50 bytes, ARM
 * func_ov066_022670d8 @ 0x022670d8, 0x60 bytes, ARM
 * func_ov066_02267088 @ 0x02267088, 0x50 bytes, ARM
 * func_ov066_02267038 @ 0x02267038, 0x50 bytes, ARM
 * func_ov066_02266fd8 @ 0x02266fd8, 0x60 bytes, ARM
 * func_ov066_02266f78 @ 0x02266f78, 0x60 bytes, ARM
 * func_ov066_02266e70 @ 0x02266e70, 0x108 bytes, ARM
 * func_ov066_02266e64 @ 0x02266e64, 0xc bytes, ARM
 * func_ov066_02266e08 @ 0x02266e08, 0x5c bytes, ARM
 * func_ov066_02266dbc @ 0x02266dbc, 0x4c bytes, ARM
 * func_ov066_02266ce8 @ 0x02266ce8, 0xd4 bytes, ARM
 */

#include "types.h"

typedef struct {
    int type;
    int val;
} UnkStruct_02267348;

typedef struct UnkStruct_022672b8 {
    int cur; // 0x00
    unsigned char pad_04[0x30 - 4];
    int unk_30; // 0x30
    int unk_34; // 0x34
    unsigned char pad_38[4];
    u32 lo : 11;  // 0x3c, bits 0..10
    int busy : 1; // bit 11
    u32 hi : 20;
} UnkStruct_022672b8;

typedef struct UnkStruct_02266e08 {
    unsigned char pad_00[0x16];
    unsigned char unk_16;
    unsigned char pad_17[0x25];
    unsigned long bits0 : 10;
    signed long bit10 : 1;
    unsigned long bits11 : 21;
} UnkStruct_02266e08;

typedef struct Ctl {
    unsigned char pad_00[4];
    u32 state; // 0x04
} Ctl;

extern int *data_ov066_0226bdec;
extern void func_ov066_02266b54(int param);
extern void func_ov066_02268370(unsigned int);
extern void func_ov066_022682cc(void);
extern void func_ov066_02269728(void);
extern void func_ov066_02268098(void);
extern void func_ov066_02267be0(void);
extern void func_ov066_02268d08(void);
extern void func_ov066_0226686c(int);
extern void func_ov066_0226696c(void *packet);
extern void func_ov066_02266a08(void (*)(void *));
int WM_GetLinkLevel(void);

void func_ov066_02266e70(void);
void func_ov066_02266e64(void);
void func_ov066_02266dbc(void);

int func_ov066_02267348(void)
{
    int result = 0;
    UnkStruct_02267348 *p = (*(UnkStruct_02267348 **) &data_ov066_0226bdec);
    switch (p->type) {
        case 0:
            result = (p->val == 2);
            break;
        case 1:
            result = (p->val == 3);
            break;
        case 2:
            result = (p->val == 4);
            break;
        case 3:
            result = (p->val == 10);
            break;
        case 4:
            result = (p->val == 7);
            break;
        case 5:
            result = (p->val == 11);
            break;
        case 6:
            result = (p->val == 10) || (p->val == 11);
            break;
    }
    return result;
}

int func_ov066_022672b8(int state, int a, int b)
{
    if ((*(UnkStruct_022672b8 **) &data_ov066_0226bdec) == 0) {
        return 0;
    }
    if (state >= 7 || state == (*(UnkStruct_022672b8 **) &data_ov066_0226bdec)->cur) {
        return 0;
    }
    (*(UnkStruct_022672b8 **) &data_ov066_0226bdec)->cur = state;
    (*(UnkStruct_022672b8 **) &data_ov066_0226bdec)->unk_30 = a;
    (*(UnkStruct_022672b8 **) &data_ov066_0226bdec)->unk_34 = b;
    if ((*(UnkStruct_022672b8 **) &data_ov066_0226bdec)->busy == 0) {
        (*(UnkStruct_022672b8 **) &data_ov066_0226bdec)->busy = 1;
        func_ov066_02266e70();
    }
    return 1;
}

void func_ov066_0226727c(void)
{
    int v = *data_ov066_0226bdec;
    if (v <= 0) {
        return;
    }
    func_ov066_02266b54(0);
}

void func_ov066_02267224(void)
{
    int v = *data_ov066_0226bdec;
    if (v < 1) {
        func_ov066_02266b54(1);
    } else if (v > 1) {
        func_ov066_02266b54(2);
    }
}

void func_ov066_02267188(void)
{
    switch (*(*(unsigned int **) &data_ov066_0226bdec)) {
        case 0:
        case 1:
            func_ov066_02266b54(3);
            break;
        case 3:
            func_ov066_02268370(0x0000bd8a);
            break;
        case 4:
            func_ov066_022682cc();
            break;
        case 5:
            func_ov066_02269728();
            break;
        case 6:
            func_ov066_02268098();
            break;
    }
}

void func_ov066_02267138(void)
{
    int v = *data_ov066_0226bdec;
    switch (v) {
        case 0:
        case 1:
        case 2:
        case 4:
        case 5:
        case 6:
            func_ov066_02266e64();
            break;
        default:
            break;
    }
}

void func_ov066_022670d8(void)
{
    int v = *data_ov066_0226bdec;
    switch (v) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 6:
            func_ov066_02266e64();
            return;
        case 5:
            func_ov066_02267be0();
            return;
        case 4:
        default:
            return;
    }
}

void func_ov066_02267088(void)
{
    int v;
    v = *data_ov066_0226bdec;
    switch (v) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 6:
            func_ov066_02266e64();
            break;
        case 5:
        default:
            break;
    }
}

void func_ov066_02267038(void)
{
    int x = *data_ov066_0226bdec;
    switch (x) {
        case 0:
        case 1:
        case 2:
            func_ov066_02266e64();
            break;
        case 3:
        case 4:
        case 5:
        case 6:
        default:
            break;
    }
}

void func_ov066_02266fd8(void)
{
    unsigned int val = *(*(unsigned int **) &data_ov066_0226bdec);
    switch (val) {
        case 0:
        case 1:
        case 2:
        case 4:
        case 6:
            func_ov066_02266e64();
            break;
        case 5:
            func_ov066_02268d08();
            break;
        case 3:
        default:
            break;
    }
}

void func_ov066_02266f78(void)
{
    unsigned int val = *(*(unsigned int **) &data_ov066_0226bdec);
    switch (val) {
        case 0:
        case 1:
        case 2:
        case 4:
        case 6:
            func_ov066_02266e64();
            break;
        case 3:
            func_ov066_02268d08();
            break;
        case 5:
        default:
            break;
    }
}

void func_ov066_02266e70(void)
{
    unsigned int cmd;
    cmd = (*(struct UnkStruct_02266e70 {
              unsigned int unk_00;
              unsigned int cmd;
          } **) &data_ov066_0226bdec)
              ->cmd;
    switch (cmd) {
        case 2:
            func_ov066_0226727c();
            break;
        case 3:
            func_ov066_02267224();
            break;
        case 4:
            func_ov066_02267188();
            break;
        case 6:
            func_ov066_02267138();
            break;
        case 7:
            func_ov066_022670d8();
            break;
        case 8:
            func_ov066_02267088();
            break;
        case 5:
            func_ov066_02267038();
            break;
        case 10:
            func_ov066_02266fd8();
            break;
        case 11:
            func_ov066_02266f78();
            break;
        case 0:
        case 1:
            func_ov066_0226686c(0x44);
            break;
        case 9:
        default:
            func_ov066_02266e64();
            break;
    }
}

void func_ov066_02266e64(void)
{
    func_ov066_02266dbc();
}

int func_ov066_02266e08(void)
{
    int result = 0;
    UnkStruct_02266e08 *p = (*(UnkStruct_02266e08 **) &data_ov066_0226bdec);
    if (p->bit10) {
        result = 1;
    } else if (p->unk_16 == 1) {
        func_ov066_02266dbc();
        result = 1;
    }
    return result;
}

void func_ov066_02266dbc(void)
{
    unsigned int x = (*(unsigned int **) &data_ov066_0226bdec)[1];
    switch (x) {
        case 0:
        case 1:
        case 2:
        case 3:
            break;
        default:
            func_ov066_02266a08(func_ov066_0226696c);
            break;
    }
}

int func_ov066_02266ce8(void)
{
    switch ((*(Ctl **) &data_ov066_0226bdec)->state) {
        case 10:
        case 11:
            switch (WM_GetLinkLevel()) {
                case 0:
                    return 0;
                case 1:
                    return 1;
                case 2:
                    return 2;
                case 3:
                    return 3;
            }
            break;
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            return 4;
    }
    return 5;
}
