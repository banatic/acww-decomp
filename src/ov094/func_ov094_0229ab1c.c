/* func_ov094_0229ab1c @ 0x0229ab1c, 0x40 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov094_0229a8bc(void *p, unsigned char c);
extern void func_ov094_0229ab5c(void *p);

void func_ov094_0229ab1c(void *p, int b)
{
    if (func_ov094_0229a8bc(p, (unsigned char) b)) {
        func_ov094_0229ab5c(p);
    } else {
        if (*(unsigned char *) ((char *) p + 0xa56) != b) {
            *(unsigned char *) ((char *) p + 0xa56) = (unsigned char) b;
            *(unsigned char *) ((char *) p + 0xa57) = 2;
        }
    }
}
