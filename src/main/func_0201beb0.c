/* func_0201beb0 @ 0x0201beb0, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02085148(void *);
extern void MI_CpuCopy8(void *, void *, int);

int func_0201beb0(void *a, int *b, int *c, void *d)
{
    void *p;
    int r;

    p = (void *) ((char *) a + 0xea);
    r = func_02085148(p);
    if (r != 0) {
        *b = *(unsigned char *) ((char *) r + 0xf);
        *c = *(unsigned char *) ((char *) r + 0x10);
        MI_CpuCopy8((char *) r + 0x11, d, 0xd);
        return 1;
    }
    return 0;
}
