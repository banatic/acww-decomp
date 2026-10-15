/* func_ov066_0226b90c @ 0x0226b90c, 0xac bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

#pragma optimize_for_speed
#pragma opt_speed

extern int WM_SetPortCallback(int, int, int);
extern void func_ov066_022668c4(void *);
extern void func_ov066_02269aa4(void);

typedef struct {
    void *unk_00;
    void *unk_04;
    void *unk_08;
    void *unk_0C;
    void *unk_10;
    void *unk_14;
    void *unk_18;
    void *unk_1C;
    void *unk_20;
    void *unk_24;
    void *unk_28;
    void *unk_2C;
    void *unk_30;
} UnkStruct_0226b90c;

extern UnkStruct_0226b90c *data_ov066_0226be08;

void func_ov066_0226b90c(void)
{
    if (data_ov066_0226be08 == 0) {
        return;
    }
    WM_SetPortCallback(12, 0, 0);
    WM_SetPortCallback(13, 0, 0);
    func_ov066_022668c4(data_ov066_0226be08->unk_18);
    func_ov066_022668c4(data_ov066_0226be08->unk_0C);
    func_ov066_022668c4(data_ov066_0226be08->unk_08);
    func_ov066_022668c4(data_ov066_0226be08->unk_30);
    func_ov066_022668c4(data_ov066_0226be08);
    func_ov066_02269aa4();
    data_ov066_0226be08 = 0;
}
