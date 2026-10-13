/* func_02080a4c @ 0x02080a4c, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuFill8(void *dst, int val, int size);
extern void MI_CpuCopy8(void *dst, const void *src, int size);

void func_02080a4c(void *param0, void *param1, int param2)
{
    int r4;
    void *r5;
    void *r6;

    r5 = param0;
    r6 = param1;
    r4 = param2;

    MI_CpuFill8((char *) r5 + 0x7c6, 0, 8);

    if (r4 > 4) {
        r4 = 4;
    }

    MI_CpuCopy8(r6, (char *) r5 + 0x7c6, r4 << 1);
}
