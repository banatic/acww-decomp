/* func_0209df04 @ 0x0209df04, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209e5b4(void *, void *);

void func_0209df04(unsigned char *p)
{
    unsigned int stack[8];
    func_0209e5b4(stack, &stack[4]);
    *(unsigned int *) p = 0;
    *(unsigned int *) (p + 4) = 0;
    p[5] = (unsigned char) stack[0];
    p[4] = (unsigned char) stack[1];
    p[3] = (unsigned char) stack[2];
    p[2] = (unsigned char) stack[4];
    p[1] = (unsigned char) stack[5];
    p[0] = (unsigned char) stack[6];
}
