/* func_ov121_0229a6b4 @ 0x0229a6b4, 0x114 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

// Two switches: a 6-entry table over 9..0xE, then 0/1/2 on the result.

typedef struct UnkStruct_0229a6b4 {
    char pad_00[0xae];
    u8 unk_AE;
    u8 unk_AF;
} UnkStruct_0229a6b4;

extern unsigned int func_020b2300(void);
extern void func_ov121_0229af7c(UnkStruct_0229a6b4 *, int, int);
extern void RtcSendPxiCommand(int);
extern int func_ov121_0229abac(UnkStruct_0229a6b4 *, u8);
extern unsigned char *func_ov121_0229afb8(UnkStruct_0229a6b4 *);
extern int func_ov121_0229a50c(void);
extern void func_ov121_02299c88(UnkStruct_0229a6b4 *, u8);
extern int func_ov004_0223c660(void *);
extern int func_ov004_0223b3f8(void **, u8, int);
extern int func_ov004_0223b440(void **, u8, int);
extern int func_ov004_0223b488(void **, u8, int);
extern int func_ov004_0223b4d0(void **, u8, int);

void func_ov121_0229a6b4(UnkStruct_0229a6b4 *o)
{
    void *h;
    int r;

    if (func_020b2300() > 1) {
        func_ov121_0229af7c(o, 9, 0);
        RtcSendPxiCommand(0x73);
        return;
    }
    switch (o->unk_AF) {
        case 0xd:
            r = func_ov004_0223b4d0(&h, (u8) func_ov121_0229abac(o, o->unk_AE), 1);
            break;
        case 0xc:
            r = func_ov004_0223b440(&h, (u8) func_ov121_0229abac(o, o->unk_AE), 1);
            break;
        case 9:
            r = func_ov004_0223b3f8(&h, (u8) func_ov121_0229abac(o, o->unk_AE), 1);
            break;
        case 0xe:
            r = func_ov004_0223b488(&h, (u8) func_ov121_0229abac(o, o->unk_AE), 1);
            break;
        case 0xa:
        case 0xb:
        default:
            func_ov121_0229afb8(o);
            return;
    }
    switch (r) {
        case 0:
        case 1:
            func_ov121_0229af7c(o, 5, 0);
            RtcSendPxiCommand(0x73);
            break;
        case 2:
            func_ov121_0229af7c(o, 3, 0);
            RtcSendPxiCommand(0x73);
            break;
        default:
            asm {
                mov r0, o
            }
            func_ov121_0229a50c();
            func_ov004_0223c660(h);
            func_ov121_0229afb8(o);
            func_ov121_02299c88(o, o->unk_AF);
            break;
    }
}
