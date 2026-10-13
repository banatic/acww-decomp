/* func_0203d668 @ 0x0203d668, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0203ddfc(void *ptr);
extern void MI_CpuFill8(void *ptr, int value, int size);

void func_0203d668(void *arg0)
{
    void *ptr;
    int i;

    ptr = arg0;
    func_0203ddfc((char *) ptr + 0x5c);
    MI_CpuFill8((char *) ptr + 0x30c, 0, 0x200);
    i = -1;
    *(int *) ((char *) ptr + 0x50c) = i;
}
