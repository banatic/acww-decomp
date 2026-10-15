/* func_020ecce4 @ 0x020ecce4, 0x104 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

extern void MI_CpuFill8(void *dest, u8 fill, u32 size);
extern int func_020edaf0(int size, int align);
extern int UTi_PutString(int pointer);
extern void func_020ed6e8(unsigned char *command);
extern void CTRDG_WriteAgbFlashSectorAsync(int index, char *buffer, unsigned int length);
extern int func_ov066_022667e0(void (*fp)(unsigned char *));
extern void func_ov066_02267fe8(void (*callback)(int, char *, unsigned int));
extern int func_ov066_022672b8(int, int, int);

extern void (*CTRDGi_WriteAgbFlashSectorAsync)(int, char *, unsigned int);
extern u8 data_021fbef8;
extern u8 data_021fbf68[16];
extern u8 data_021fbef4;
extern u32 data_021fbf20;
extern u8 data_0213e6b4;

typedef struct MSG {
    u32 x;
    u8 c0;
    u8 c1;
    u8 c2;
    u8 c3;
} MSG;

extern int func_ov066_0226b9b8(MSG *msg);
extern int func_ov066_0226748c(int a, int (*allocator)(int, int), int (*deallocator)(int), int d);

void func_020ecce4(int action, void (*data)(int, char *, unsigned int))
{
    MSG msg;

    CTRDGi_WriteAgbFlashSectorAsync = data;
    data_021fbef8 = (u8) action;
    MI_CpuFill8(data_021fbf68, 0, 16);

    msg.x = data_021fbf20;
    msg.c0 = data_021fbef4;
    msg.c2 = 60;
    msg.c3 = 2;
    msg.c1 = 8;

    func_ov066_0226748c(data_0213e6b4, func_020edaf0, UTi_PutString, 0);

    func_ov066_022667e0(func_020ed6e8);
    func_ov066_0226b9b8(&msg);
    func_ov066_02267fe8(CTRDG_WriteAgbFlashSectorAsync);

    if (action == 1) {
        func_ov066_022672b8(3, 0, 0);
        return;
    }

    if (action == 2) {
        func_ov066_022672b8(4, 0, 0);
    }
}
