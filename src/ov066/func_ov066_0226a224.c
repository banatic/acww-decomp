/* func_ov066_0226a224 @ 0x0226a224, 0x54 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

extern int WM_GetAllowedChannel(void);
extern int MATH_CountPopulation(void);
extern void func_ov066_0226686c(int);

typedef struct {
    unsigned char pad_00[0x90];
    unsigned short unk_90;
    unsigned char unk_92;
} S_226a224;

extern S_226a224 *data_ov066_0226bdf4;

void func_ov066_0226a224(void)
{
    int v;

    v = WM_GetAllowedChannel();
    if (v == 0) {
        func_ov066_0226686c(0x41);
        return;
    } else {
        data_ov066_0226bdf4->unk_90 = v;
        data_ov066_0226bdf4->unk_92 = MATH_CountPopulation();
        return;
    }
}
