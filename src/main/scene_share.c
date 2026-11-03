/* scene_share: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0201bee0 @ 0x0201bee0, 0x44 bytes, Thumb
 * func_0201beb0 @ 0x0201beb0, 0x30 bytes, Thumb
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

int func_0201beb0(void *a, int *b, int *c, void *d)
{
    void *p;
    int r;

    p = (void *) ((char *) a + 0xea);
    r = (int) func_02085148(p);
    if (r != 0) {
        *b = *(unsigned char *) ((char *) r + 0xf);
        *c = *(unsigned char *) ((char *) r + 0x10);
        MI_CpuCopy8((char *) r + 0x11, d, 0xd);
        return 1;
    }
    return 0;
}
