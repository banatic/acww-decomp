/* func_ov066_02267404 @ 0x02267404, 0x88 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

struct OverlayState {
    int pad_00;
    int state;
};

extern struct OverlayState *data_ov066_0226bdec; // 0x0226bdec
extern int (*data_ov066_0226bde8)(int, int);     // 0x0226bde8
extern int (*data_ov066_0226bde4)(int);          // 0x0226bde4
extern int data_ov066_0226bde0;                  // 0x0226bde0

extern void func_ov066_022668c4(struct OverlayState *);
extern void func_ov066_0226686c(int);

int func_ov066_02267404(void)
{
    if (data_ov066_0226bdec->state == 1) {
        data_ov066_0226bdec->state = 0;
        func_ov066_022668c4(data_ov066_0226bdec);
        data_ov066_0226bde8 = 0;
        data_ov066_0226bde4 = 0;
        data_ov066_0226bde0 = 0;
        data_ov066_0226bdec = 0;
        return 1;
    } else {
        func_ov066_0226686c(0x44);
        return 0;
    }
}