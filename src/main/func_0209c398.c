/* func_0209c398 @ 0x0209c398, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209c52c(void *ptr);
extern void MI_CpuFill8(void *ptr, int val, int size);

void func_0209c398(void *arg)
{
    void *ptr = arg;
    MI_CpuFill8(ptr, 0, 0x24);
    *(unsigned char *) ((char *) ptr + 0x10) = 7;
    func_0209c52c((char *) ptr + 0x11);
    func_0209c52c((char *) ptr + 0x19);
    *(unsigned int *) ptr = 0;
    *(unsigned int *) ((char *) ptr + 4) = 0;
    *(unsigned int *) ((char *) ptr + 8) = 0;
    *(unsigned int *) ((char *) ptr + 0xc) = 0;
}
