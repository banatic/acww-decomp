/* func_02075278 @ 0x02075278, 0x2e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuCopy8(const void *src, void *dst, unsigned int size);
extern void func_020984e8(void);
extern int func_020989e0(void);

void func_02075278(unsigned char *arg0, int arg1)
{
    unsigned int local;
    int ret;

    MI_CpuCopy8(arg0, &local, 4);
    func_020984e8();
    ret = func_020989e0();
    MI_CpuCopy8(arg0 + 4, (void *) (ret + local), arg1 - 4);
}
