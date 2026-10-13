/* func_02081b68 @ 0x02081b68, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuFill8(void *a, void *b, int c);
extern void MI_CpuCopy8(void *a, void *b, int c);

void func_02081b68(void *a, void *b, int c)
{
    void *p;
    int i;
    unsigned short *s;

    p = (void *) ((char *) a + 0x2a);
    MI_CpuFill8(p, 0, 0x14);
    if (c > 10) {
        c = 10;
    }
    MI_CpuCopy8(b, (char *) a + 0x2a, c << 1);
    s = (unsigned short *) ((char *) a + 0x7c);
    *s |= 2;
}
