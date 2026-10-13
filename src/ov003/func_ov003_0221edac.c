/* func_ov003_0221edac @ 0x0221edac, 0x24 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern unsigned long data_ov003_02239754;
extern unsigned long data_ov003_02239818;
extern void func_ov009_0226539c(void *p);

unsigned long *func_ov003_0221edac(unsigned long *p)
{
    p[0] = (unsigned long) &data_ov003_02239754;
    p[59] = (unsigned long) &data_ov003_02239818;
    func_ov009_0226539c(p);
    return p;
}
