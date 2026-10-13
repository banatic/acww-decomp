/* func_0201a720 @ 0x0201a720, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuFill8(void *dst, unsigned int value, unsigned int size);

void func_0201a720(int unused, int *ptr, int count)
{
    int i;
    unsigned int fill = 0;

    for (i = 0; i < count; i++) {
        MI_CpuFill8(ptr, fill, 4);
        *(short *) ptr = -1;
        ptr++;
    }
}
