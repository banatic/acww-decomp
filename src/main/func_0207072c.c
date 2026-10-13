/* func_0207072c @ 0x0207072c, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02077ed4(void *);
extern void *func_020e9958(void *, int);
extern void MI_CpuCopy8(void *, void *, int);
extern void func_020e993c(void *, void *);

extern unsigned char data_021fbe94[];

void func_0207072c(void *arg0)
{
    void *r6;
    void *r4;
    void *r0;

    r6 = *(void **) data_021fbe94;
    r4 = func_020e9958(r6, 0xc0);
    MI_CpuCopy8((char *) arg0 + 1, r4, 0xc0);
    func_02077ed4(r4);
    func_020e993c(r6, r4);
}
