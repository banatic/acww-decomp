/* func_020010c0 @ 0x020010c0, 0x178 bytes, ARM, module main
 * mwccarm 1.2/base -O4,s
 */

extern void DC_InvalidateRange(void *c, int val);
extern void OS_SpinWait(int delay);
extern int PXI_SendWordByFifo(int cmd, int param, int zero);

extern volatile int data_0213fdc0;

void func_020010c0(unsigned int a, unsigned int b, void *c)
{
    unsigned int mask = 0xffff;
    unsigned int c_val = (unsigned int) c;
    unsigned int a_hi = a >> 16;
    unsigned int a_lo = a & mask;
    unsigned int sb = 0x02002300 | (a_hi & 0xff);
    unsigned int fp = 0x40000 | (c_val >> 16);
    unsigned int b_hi = b >> 16;
    unsigned int b_lo = b & mask;
    unsigned int r8 = 0x10000 | a_lo;
    unsigned int r7 = 0x20000 | b_hi;
    unsigned int r6 = 0x30000 | b_lo;
    unsigned int val2 = 0x01050000 | (c_val & mask);
    int val3 = 0x20;
    int zero = 0;
    int four = 4;
    int val4 = 1;

    while (1) {
        int ok;
        data_0213fdc0 = zero;
        DC_InvalidateRange(c, val3);

        goto check_start;
        do {
            OS_SpinWait(0x186a0);
        check_start:
            if (PXI_SendWordByFifo(four, sb, zero) < 0) {
                ok = zero;
            } else if (PXI_SendWordByFifo(four, r8, zero) < 0) {
                ok = zero;
            } else if (PXI_SendWordByFifo(four, r7, zero) < 0) {
                ok = zero;
            } else if (PXI_SendWordByFifo(four, r6, zero) < 0) {
                ok = zero;
            } else if (PXI_SendWordByFifo(four, fp, zero) < 0) {
                ok = zero;
            } else if (PXI_SendWordByFifo(four, val2, zero) < 0) {
                ok = zero;
            } else {
                ok = val4;
            }
        } while (ok == 0);

        while (data_0213fdc0 == 0) {
        }

        if (data_0213fdc0 == 1) {
            return;
        }
    }
}
