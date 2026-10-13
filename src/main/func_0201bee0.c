/* func_0201bee0 @ 0x0201bee0, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02085148(void *);
extern void func_02077978(void *, void *, void *);
extern void MI_CpuCopy8(void *, void *, int);

int func_0201bee0(unsigned char *p, char *a, char *b)
{
    char *r;
    if (p[0x563] != 0) {
        goto fail;
    }
    r = (char *) func_02085148(p + 0xea);
    if (r == 0) {
        goto fail;
    }
    func_02077978(r + 4, a, a + 8);
    MI_CpuCopy8(r + 9, b, 2);
    return 1;
fail:
    return 0;
}
