/* func_ov096_0229ffe0 @ 0x0229ffe0, 0x94 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O1,s
 */

extern int func_ov002_02208e18(const void *);
extern int func_ov096_0229c2fc(const void *, int);
extern int func_ov002_02208a78(const void *, unsigned char);
extern void func_ov096_0229c454(void *);
extern int func_0206fcbc(void);
extern int func_ov002_02208a24(const void *, int, unsigned char);
extern int func_ov002_02208ad0(const void *);
extern unsigned char *func_ov096_0229cbe0(void *, int);
extern void func_ov096_0229fb9c(void *);

void func_ov096_0229ffe0(void *base)
{
    if (func_ov002_02208e18((char *) base + 0x2564) == 0) {
        return;
    }
    if (func_ov096_0229c2fc(base, 0x200) != 0 &&
        func_ov002_02208a78((char *) base + 0x2564, *(unsigned char *) ((char *) base + 0xbe)) == 1) {
        func_ov096_0229c454(base);
        return;
    }
    {
        int n;
        if (func_ov002_02208a24((char *) base + 0x2564, func_0206fcbc(), *(unsigned char *) ((char *) base + 0xbe)) == 2) {
            *(unsigned char *) ((char *) base + 0xbd) = *(unsigned char *) ((char *) base + 0xbd) + 1;
            n = func_ov002_02208ad0((char *) base + 0x2564);
            if ((unsigned) *(unsigned char *) ((char *) base + 0xbd) >= (unsigned) n) {
                *(unsigned char *) ((char *) base + 0xbd) = 0;
            }
            func_ov096_0229cbe0(base, 0);
        } else {
            func_ov096_0229fb9c(base);
        }
    }
}
