/* local_session_2: 2 functions, module ov066
 * mwccarm 1.2/base -O4,p
 * func_ov066_0226a224 @ 0x0226a224, 0x54 bytes, ARM
 * func_ov066_0226a1b0 @ 0x0226a1b0, 0x74 bytes, ARM
 */

typedef struct {
    unsigned char pad_00[0x90];
    unsigned short unk_90;
    unsigned char unk_92;
} S_226a224;

extern int WM_GetAllowedChannel(void);
extern int MATH_CountPopulation(unsigned int bits);
extern void func_ov066_0226686c(int);
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
        data_ov066_0226bdf4->unk_92 = MATH_CountPopulation((unsigned int) v);
        return;
    }
}

unsigned short func_ov066_0226a1b0(unsigned short x)
{
    unsigned short flags = *(unsigned short *) ((char *) (*(unsigned char * *) &data_ov066_0226bdf4) + 0x90);
    unsigned short cur = x;
    unsigned short i;
    i = 0;
    do {
        cur = (unsigned short) (cur + 1);
        if (cur > 14) {
            cur = 1;
        }
        if (flags & (1 << (cur - 1))) {
            return cur;
        }
    } while (++i < 14);
    return x;
}
