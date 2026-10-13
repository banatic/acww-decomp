/* func_020b1b0c @ 0x020b1b0c, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char SDK_OVERLAY_ov000_ID;
extern void func_0204fa5c(unsigned int *buf, unsigned int val);
extern void MIi_CpuClearFast(unsigned int val, unsigned int *ptr, unsigned int size);
extern void DC_FlushRange(unsigned int *ptr, unsigned int size);

void func_020b1b0c(void)
{
    volatile struct {
        unsigned int x;
        unsigned int buf[12];
    } t;
    unsigned int *p;
    unsigned int size;

    func_0204fa5c((unsigned int *) t.buf, (unsigned int) &SDK_OVERLAY_ov000_ID);
    p = (unsigned int *) t.buf[1];
    t.x = 0xe7fee7fe;
    size = 0x022a3300 - (unsigned int) p;
    MIi_CpuClearFast(t.x, p, size);
    DC_FlushRange(p, size);
}
