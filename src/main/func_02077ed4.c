/* func_02077ed4 @ 0x02077ed4, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02078148(void *addr);
extern void func_0209df64(int *p);
extern void func_020782a0(void *handle, int *p);
extern void func_02078224(void *handle);
extern int func_020782cc(void *handle);
extern void MI_CpuCopy8(void *a, int b, int c);

extern unsigned char data_021eed68[];

void func_02077ed4(void *param)
{
    void *handle;
    int local;

    handle = func_02078148((void *) data_021eed68);
    func_0209df64(&local);
    func_020782a0(handle, &local);
    func_02078224(handle);
    MI_CpuCopy8(param, func_020782cc(handle), 0xc0);
}
