/* func_02075278 @ 0x02075278, 0x2e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuCopy8(const void *src, void *dst, unsigned int size);
extern int func_020984e8(void);
extern int func_020989e0(int object);

void func_02075278(unsigned char *payload, unsigned int length, int player)
{
    unsigned int local;
    int ret;

    MI_CpuCopy8(payload, &local, 4);
    ret = func_020989e0(func_020984e8());
    MI_CpuCopy8(payload + 4, (void *) (ret + local), length - 4);
}
