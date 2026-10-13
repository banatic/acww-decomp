/* func_0201bfd8 @ 0x0201bfd8, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02085148(void *ptr);
extern void MI_CpuCopy8(char *ptr, int a, unsigned int b) __attribute__((target("arm")));

int func_0201bfd8(char *param0, int param1, unsigned int param2)
{
    void *ptr;
    if (*(unsigned char *) (param0 + 0x563) != 0) {
        goto fail;
    }
    ptr = func_02085148(param0 + 0xEA);
    if (param2 > 4) {
        param2 = 4;
    }
    if (ptr == 0) {
        goto fail;
    }
    MI_CpuCopy8((char *) ptr + 0x0B, param1, param2);
    return 1;
fail:
    return 0;
}
