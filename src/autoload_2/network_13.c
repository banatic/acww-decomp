/* network_13: 3 functions, module autoload_2
 * mwccarm 1.2/base -O4,p
 * func_020ecde8 @ 0x020ecde8, 0x6c bytes, ARM
 * func_020ecce4 @ 0x020ecce4, 0x104 bytes, ARM
 * func_020ecba8 @ 0x020ecba8, 0x13c bytes, ARM
 */

#include "types.h"

typedef struct MSG {
    u32 x;
    u8 c0;
    u8 c1;
    u8 c2;
    u8 c3;
} MSG;

extern unsigned char data_021fbef8;
extern unsigned short data_021fbefc;
extern void DWC_ProcessInet(void);
extern void func_ov065_02278000(void);
extern int func_ov065_0227f700(void);
extern void func_020ed03c(void);
extern void func_020ecf24(void);
extern void MI_CpuFill8(void *dest, u8 fill, u32 size);
extern int func_020edaf0(int size, int align);
extern int func_020edacc(int pointer);
extern void func_020ed6e8(unsigned char *command);
extern void func_020ed6c4(int index, char *buffer, unsigned int length);
extern int func_ov066_022667e0(void (*fp)(unsigned char *));
extern void func_ov066_02267fe8(void (*callback)(int, char *, unsigned int));
extern int func_ov066_022672b8(int, int, int);
extern void (*CTRDGi_WriteAgbFlashSectorAsync)(int, char *, unsigned int);
extern u8 data_021fbf68[16];
extern u8 data_021fbef4;
extern u32 data_021fbf20;
extern u8 data_0213e6b4;
extern int func_ov066_0226b9b8(MSG *msg);
extern int func_ov066_0226748c(int a, int (*allocator)(int, int), int (*deallocator)(int), int d);
extern int data_021fbf30;
extern int data_021fbf40;
extern char *data_021fbf3c;
extern short data_021fbf00;
extern int data_0213e6bc;
extern int data_0213e6c0;
extern int data_021fbf1c;
extern int data_021fbf2c;
extern int data_021fbf44;
extern int data_021fbf4c;
extern int data_021fbf14;
extern int data_021fbf10;
extern int data_021fbf0c;
extern int data_021fbf34;
extern char data_021fbff8[0x40];
extern int func_020edab8(int unused, int size, int align);
extern void func_020edaa8(int unused, int pointer);
extern void func_ov065_0227f1f4(unsigned int allocator, unsigned int deallocator);

void func_020ecde8(void)
{
    unsigned char c;
    unsigned short s;

    c = data_021fbef8;
    c = (unsigned char) (c + 0xfd);
    if (c > 1) {
        return;
    }

    s = data_021fbefc;
    if (s == 1) {
        DWC_ProcessInet();
        return;
    }

    func_ov065_02278000();
    func_ov065_0227f700();
    func_020ed03c();
    func_020ecf24();
}

void func_020ecce4(int action, void (*data)(int, char *, unsigned int))
{
    MSG msg;

    CTRDGi_WriteAgbFlashSectorAsync = data;
    (*(u8 *) &data_021fbef8) = (u8) action;
    MI_CpuFill8(data_021fbf68, 0, 16);

    msg.x = data_021fbf20;
    msg.c0 = data_021fbef4;
    msg.c2 = 60;
    msg.c3 = 2;
    msg.c1 = 8;

    func_ov066_0226748c(data_0213e6b4, func_020edaf0, func_020edacc, 0);

    func_ov066_022667e0(func_020ed6e8);
    func_ov066_0226b9b8(&msg);
    func_ov066_02267fe8(func_020ed6c4);

    if (action == 1) {
        func_ov066_022672b8(3, 0, 0);
        return;
    }

    if (action == 2) {
        func_ov066_022672b8(4, 0, 0);
    }
}

void func_020ecba8(int a0, void (*a1)(int, char *, unsigned int), int a2, int a3, char *a4)
{
    unsigned int i;
    char *p;
    (*(char *) &data_021fbef8) = (unsigned char) a0;
    CTRDGi_WriteAgbFlashSectorAsync = a1;
    data_021fbf40 = a3;
    data_021fbf3c = a4;
    data_021fbf30 = a2;
    (*(short *) &data_021fbefc) = 0;
    data_021fbf00 = 0;
    data_0213e6bc = 0;
    data_0213e6c0 = 1;
    data_021fbf1c = 0;
    data_021fbf2c = 0;
    data_021fbf44 = 0;
    data_021fbf4c = 0;
    data_021fbf14 = 0;
    data_021fbf10 = 0;
    data_021fbf0c = 0;
    data_021fbf34 = 0;
    MI_CpuFill8(data_021fbff8, 0, 0x40);
    for (i = 0; i < 32; i++) {
        p = data_021fbf3c + (i * 0x23);
        p[0x1a0] = 0;
    }

    func_ov065_0227f1f4((unsigned int) func_020edab8, (unsigned int) func_020edaa8);
}
