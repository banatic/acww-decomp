/* func_020a2480 @ 0x020a2480, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

static void func_0209010c(void *);
extern void MI_CpuCopy8(void *, unsigned int, unsigned int);
extern char data_021ee418[];

void func_020a2480(unsigned int *arg)
{
    void *p = data_021ee418;
    func_0209010c(p);
    MI_CpuCopy8(p, arg[48], 0x950);
}
