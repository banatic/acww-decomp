/* func_02088368 @ 0x02088368, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020984e8(void *arg);
extern void *func_02099688(void *arg);
extern void *MI_CpuCopy8(void *dest, const void *src, unsigned int len);

extern char data_021dc7a8;

void *func_02088368(void *arg)
{
    char *base = &data_021dc7a8;
    void *p = func_020984e8(arg);
    if (p && base) {
        return MI_CpuCopy8(func_02099688(p), base + 0x173e2, 16);
    }
    return p;
}
