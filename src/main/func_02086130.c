/* func_02086130 @ 0x02086130, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02087f0c(void *);
extern void func_02087b78(void *);
extern void func_02087a64(void *);
extern void MI_CpuFill8(void *, int, int);

void func_02086130(void *arg0)
{
    void *r4 = arg0;
    func_02087f0c((char *) r4 + 0x18);
    MI_CpuFill8(r4, 0, 4);
    func_02087b78((char *) r4 + 0x31);
    func_02087a64((char *) r4 + 4);
}
