/* func_ov099_0229ce68 @ 0x0229ce68, 0x50 bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov099_0229cf30(int parameter0, unsigned int parameter1);
extern int func_ov099_0229cc40(void *a, void *b);
extern int func_ov099_0229cc10(void *a, void *b);
extern void func_ov099_0229ce28(void *a, unsigned char b, int c, int d);
extern void func_ov099_0229c84c(void *a, void *b);

int func_ov099_0229ce68(void *a, void *b)
{
    int resultA;
    if (func_ov099_0229cf30((int) (a), (unsigned int) (b))) {
        resultA = func_ov099_0229cc40(a, b);
        if (resultA != 0xfff1) {
            func_ov099_0229ce28(a, ((unsigned char *) a)[0x2906], resultA, func_ov099_0229cc10(a, b));
        }
        func_ov099_0229c84c(a, b);
        return 1;
    }
    return 0;
}
