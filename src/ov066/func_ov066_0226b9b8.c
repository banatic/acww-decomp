/* func_ov066_0226b9b8 @ 0x0226b9b8, 0x1c4 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

typedef void (*Fn)(void);

typedef struct UnkStruct_0226b9b8 {
    u8 unk_00;
    u8 pad_01[7];
    void *unk_08;
    void *unk_0C;
    u8 pad_10[8];
    void *unk_18;
    u8 pad_1C[0x14];
    void *unk_30;
} UnkStruct_0226b9b8;

typedef struct UnkStruct_0226b9b8_2 {
    u8 pad_00[0x9c];
    unsigned int (*unk_9C)(void);
    Fn unk_A0;
    Fn unk_A4;
    Fn unk_A8;
    void (*unk_AC)(int, int, int, int);
    int (*unk_B0)(int, int, int, int);
    int (*unk_B4)(void);
    void (*unk_B8)(int, char *, unsigned int);
    void (*unk_BC)(int);
} UnkStruct_0226b9b8_2;

typedef struct UnkStruct_0226b9b8_3 {
    u8 pad_00[0xb];
    u8 count;
} UnkStruct_0226b9b8_3;
typedef struct UnkStruct_0226b9b8_4 {
    u8 pad_00[6];
    u8 unk_06;
} UnkStruct_0226b9b8_4;

extern UnkStruct_0226b9b8 *data_ov066_0226be08;
extern UnkStruct_0226b9b8_2 *data_ov066_0226bdf4;
extern UnkStruct_0226b9b8_3 *data_ov066_0226bdec;

extern void func_ov066_0226bc4c(void *argument0);
extern void func_ov066_02269b88(void);
extern void *func_ov066_02266908(u32 size, int kind);
extern void MI_CpuFill8(void *dst, int data, u32 size);
extern void *func_ov066_0226bbb4(int kind);
extern int WM_SetPortCallback(u32 port, void *cb, void *arg);
extern int WM_SetIndCallback(void *cb);

extern unsigned int func_ov066_0226a960(void);
extern void func_ov066_0226af3c(void);
extern void func_ov066_0226af04(void);
extern void func_ov066_0226ae1c(int a, int b, int c, int callback);
extern int func_ov066_0226b81c(int a, int b, int c, int callback);
extern int func_ov066_0226b8bc(void);
extern void func_ov066_0226b90c(void);
extern void func_ov066_0226aeb8(int peer);
extern void func_ov066_0226923c(void *argument0);
extern void func_ov066_0226aab8(void *argument0);
extern void func_ov066_0226b818(void);

int func_ov066_0226b9b8(UnkStruct_0226b9b8_4 *p)
{
    u32 n;

    if (data_ov066_0226be08 != NULL) {
        return (int) p;
    }
    func_ov066_0226bc4c(p);
    func_ov066_02269b88();
    data_ov066_0226bdf4->unk_9C = func_ov066_0226a960;
    data_ov066_0226bdf4->unk_A0 = func_ov066_0226af3c;
    data_ov066_0226bdf4->unk_A4 = func_ov066_0226af04;
    data_ov066_0226bdf4->unk_AC = func_ov066_0226ae1c;
    data_ov066_0226bdf4->unk_B0 = func_ov066_0226b81c;
    data_ov066_0226bdf4->unk_B4 = func_ov066_0226b8bc;
    data_ov066_0226bdf4->unk_A8 = func_ov066_0226b90c;
    data_ov066_0226bdf4->unk_BC = func_ov066_0226aeb8;

    data_ov066_0226be08 = (UnkStruct_0226b9b8 *) func_ov066_02266908(0x34, 4);

    n = (u32) data_ov066_0226bdec->count << 4;
    data_ov066_0226be08->unk_30 = func_ov066_02266908(n, 4);
    MI_CpuFill8(data_ov066_0226be08->unk_30, 0, n);

    data_ov066_0226be08->unk_08 = func_ov066_0226bbb4(3);
    data_ov066_0226be08->unk_0C = func_ov066_0226bbb4(3);

    n = (u32) data_ov066_0226bdec->count << 2;
    data_ov066_0226be08->unk_18 = func_ov066_02266908(n, 4);
    MI_CpuFill8(data_ov066_0226be08->unk_18, 0, n);

    data_ov066_0226be08->unk_00 = p->unk_06;
    WM_SetPortCallback(0xc, (void *) (void (*)(void *)) func_ov066_0226923c, NULL);
    WM_SetPortCallback(0xd, (void *) (void (*)(void *)) func_ov066_0226aab8, NULL);
    WM_SetIndCallback((void *) func_ov066_0226b818);
    return func_ov066_0226a960();
}
