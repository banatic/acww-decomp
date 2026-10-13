/* func_02001268 @ 0x02001268, 0x54 bytes, ARM, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02001238(void);
extern int PXI_IsCallbackReady(int, int);
extern void PXI_SetFifoRecvCallback(int, void (*)(void));

void func_02001268(void)
{
    int r5 = 4;
    int r4 = 1;
    while (PXI_IsCallbackReady(r5, r4) == 0) {
        r5 = 4;
        r4 = 1;
    }
    PXI_SetFifoRecvCallback(4, func_02001238);
    {
        volatile unsigned short *p = (volatile unsigned short *) 0x04000208;
        unsigned short old = *p;
        *p = 1;
    }
}
