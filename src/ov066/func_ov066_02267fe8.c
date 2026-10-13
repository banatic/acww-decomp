/* func_ov066_02267fe8 @ 0x02267fe8, 0x3c bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

#pragma arm

extern int *data_ov066_0226bdf4;
extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int);

void func_ov066_02267fe8(int arg)
{
    int r4 = arg;
    int state;
    if (data_ov066_0226bdf4 == 0) {
        return;
    }
    state = OS_DisableInterrupts();
    data_ov066_0226bdf4[0xb8 / 4] = r4;
    OS_RestoreInterrupts(state);
}
