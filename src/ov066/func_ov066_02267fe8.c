/* func_ov066_02267fe8 @ 0x02267fe8, 0x3c bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

#pragma arm

typedef struct CallbackState {
    unsigned char pad[0xb8];
    void (*packet)(int, char *, unsigned int);
} CallbackState;

extern CallbackState *data_ov066_0226bdf4;
extern int OS_DisableInterrupts(void);
extern unsigned int OS_RestoreInterrupts(int);

void func_ov066_02267fe8(void (*arg)(int, char *, unsigned int))
{
    void (*r4)(int, char *, unsigned int) = arg;
    int state;
    if (data_ov066_0226bdf4 == 0) {
        return;
    }
    state = OS_DisableInterrupts();
    data_ov066_0226bdf4->packet = r4;
    OS_RestoreInterrupts(state);
}
