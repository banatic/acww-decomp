/* func_0203864c @ 0x0203864c, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02038680(void *param1, int param2);
extern void MI_CpuFill8(void *param1, int param2, int param3);

void func_0203864c(void *param1)
{
    int i;
    void *ptr;

    ptr = (void *) ((char *) param1 + 0x2e4);
    MI_CpuFill8(ptr, 0x11, 0x800);
    for (i = 0; i < 4; i++) {
        func_02038680(param1, i);
    }
}
